library(ggplot2)
library(RColorBrewer)
#Sys.setlocale("LC_MESSAGES", 'en_US')

h <- 6
w <- 12

parts_input_file="partitions.csv"
qualities_input_file="qualities.csv"
details_input_file="detailed_partition.csv"
codelines_input_file="routines.csv"
parts_output_basename="parts"
qualities_output_file="qualities.pdf"
qualities2_output_file="qualities2.pdf"

cheader_parts<-c("P", "START", "END", "Function")
cheader_details<-c("P", "START", "END", "Function", "Ratio", "Callstack", "SELECTED")
cheader_codelines<-c("P", "TS", "Codeline")
cheader_qualities<-c("P", "GAIN", "LOSS")

read <- function(file, cheader) {
  df <- read.csv(file, header=FALSE, sep = ",", strip.white=TRUE)
  names(df) <- cheader
  df
}

make_plist <- function(data){
  plist<-data[["P"]]
  plist<-unique(plist)
  plist
}

inflex_p <- function(data){
  dtemp<-data
  dtemp$LOSSCOR<-dtemp$LOSS-dtemp$GAIN
  dtemp<-dtemp[(dtemp$P >0),]
  i<-which.min(dtemp[,"LOSSCOR"])
  dtemp[i,"P"]
}

inflex2_p <- function(data){
  dtemp1<-data
  dtemp2<-data
  p<-inflex_p(data)
  dtemp1<-dtemp1[(dtemp1$P %in% p),]
  xfactor<-dtemp1[1,"GAIN"]
  yfactor<-dtemp1[1,"LOSS"]
  if (xfactor>0){
    dtemp2$GAIN<-dtemp2$GAIN/xfactor
  }
  if (yfactor>0){
    dtemp2$LOSS<-dtemp2$LOSS/yfactor
  }
  dtemp2[(dtemp2$P %in% p),"GAIN"]<-1
  dtemp2[(dtemp2$P %in% p),"LOSS"]<-1
  dtemp2<-dtemp2[(dtemp2$P <=p),]
  dtemp2<-dtemp2[(dtemp2$P >0),]
  dtemp2$LOSSCOR<-dtemp2$LOSS-dtemp2$GAIN
  i<-which.min(dtemp2[,"LOSSCOR"])
  dtemp2[i,"P"]
}


print_qualities <- function(data){
  dtemp<-data
  ntemp <- data.frame(P= dtemp[2:(nrow(dtemp)),1]-0.0000001, GAIN= dtemp[1:nrow(dtemp)-1,2], LOSS= dtemp[1:nrow(dtemp)-1,3])
  ntemp[1,]<-c(1,1,1)
  dtemp<-rbind(dtemp, ntemp)
  dtemp<- dtemp[order(dtemp$P),] 
  dtemp$LABELX<-dtemp$P
  dtemp$LABELX[seq(2,nrow(dtemp),2)]<-""
  dtemp$LABELY<- with(dtemp, pmax(GAIN, LOSS))
  xlabel<- "Parameter p"
  ylabel<- "Amplitude (normalized)"
  legend<- "Quality Measures vs Parameter p"
  plot<-ggplot(dtemp, aes(x=P))
  plot<-plot + geom_line(aes(y=GAIN, colour = "Complexity reduction"))
  plot<-plot + geom_line(aes(y=LOSS, colour = "Information loss"))
  plot<-plot + theme_bw()
  plot<-plot + labs(x=xlabel,y=ylabel)
  plot<-plot + scale_colour_manual(name="Quality measures",values = c("green","red"))
  plot
}

print_qualities2 <- function(data){
  dtemp<-data
  p<-inflex_p(data)
  p2<-inflex2_p(data)
  dtemp2<-dtemp[(dtemp$P %in% p),]
  dtemp3<-dtemp[(dtemp$P %in% p2),]
  xlabel<- "Complexity reduction"
  ylabel<- "Information loss"
  plot<-ggplot()
  plot<-plot+geom_line(data=dtemp,aes(x=GAIN,y=LOSS), color="black")
  plot<-plot+geom_point(data=dtemp,aes(x=GAIN,y=LOSS), color="black")
  plot<-plot+geom_point(data=dtemp2,aes(x=GAIN,y=LOSS), color="red")
  plot<-plot+geom_point(data=dtemp3,aes(x=GAIN,y=LOSS), color="green")
  plot<-plot + theme_bw()
  plot<-plot + labs(x=xlabel,y=ylabel)
  plot
}

print_parts <- function(data, p){
  dtemp<-data[(data$P %in% p),]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel)
  plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, fill=Function), color="white", ymin=0, ymax=1)
  fnumber<-length(unique(dtemp[["Function"]]))
  getPalette = colorRampPalette(brewer.pal(9, "Set1"))
  plot<-plot+scale_fill_manual(values = getPalette(fnumber))
  plot<-plot + theme_bw()
  plot
}

print_details <- function(data, p){
  dtemp<-data[(data$P %in% p),]
  dtemp<-dtemp[order(dtemp$START, -dtemp$Callstack, dtemp$Ratio), ]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  ylabel<-  paste("Execution time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  dtemp$POSITION <-0
  dtemp$OFFSET<-0
  currentStart<-dtemp[1,"START"]
  position<-0
  offset<-0
  for (i in 2:nrow(dtemp)){
    newStart=dtemp[i,"START"]
    if (newStart != currentStart){
      currentStart<-newStart
    position<-0
    offset<-0
    }else{
      position<-position+1
      dtemp[i,"POSITION"]<-position
      offset<-offset+dtemp[i-1,"Ratio"]
      dtemp[i,"OFFSET"]<-offset
    }
  }
  dtemp<-dtemp[order(dtemp$SELECTED), ]
  dtemp2<-dtemp[(dtemp$SELECTED %in% 1), ]
  dsize=0.3
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel)
  plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=Function), color="white", size=dsize)
  plot<-plot+geom_rect(data=dtemp2, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=NA), color="black", size=dsize/3)
  fnumber<-length(unique(dtemp[["Function"]]))
  getPalette = colorRampPalette(brewer.pal(9, "Set1"))
  plot<-plot+scale_fill_manual(values = getPalette(fnumber))
  plot<-plot + theme_bw()
  plot
}

print_parts_codelines <- function(parts_data, codelines_data, p){
  parts_temp<-parts_data[(parts_data$P %in% p),]
  parts_temp<-parts_temp[!(parts_temp$Function %in% "void"),]
  codelines_temp<-codelines_data[(codelines_data$P %in% p),]
  xlabel<-paste("Time (relative), p=", p, sep="")
  legend<-paste("Relevant routines, p=", p, sep="")
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel)
  plot<-plot+scale_y_reverse()
  plot<-plot+geom_rect(data=parts_temp, mapping=aes(xmin=START, xmax=END, fill=Function), color="white", ymin=-Inf, ymax=Inf)
  #fnumber<-length(unique(parts_temp[["Function"]]))
  #getPalette = colorRampPalette(brewer.pal(9, "Set1"))
  #plot<-plot+scale_fill_manual(values = getPalette(fnumber))
  plot<-plot+geom_point(data=codelines_temp, aes(x=TS, y=Codeline), color="black", size=0.2)
  plot<-plot + theme_bw()
  plot
}

args <- commandArgs(trailingOnly = TRUE)
qualities_input <- paste(args[1],'/',qualities_input_file, sep="")
qualities_data <-read(qualities_input, cheader_qualities)
qualities_output <- paste(args[2],'/',qualities_output_file, sep="")
ggsave(qualities_output, plot = print_qualities(qualities_data), width = w, height = h)
qualities2_output <- paste(args[2],'/',qualities2_output_file, sep="")
ggsave(qualities2_output, plot = print_qualities2(qualities_data), width = w, height = h)
parts_input <- paste(args[1],'/',parts_input_file, sep="")
details_input <- paste(args[1],'/',details_input_file, sep="")
codelines_input <- paste(args[1],'/',codelines_input_file, sep="")
parts_data <-read(parts_input, cheader_parts)
details_data <-read(details_input, cheader_details)
codelines_data <-read(codelines_input, cheader_codelines)
plist<-make_plist(parts_data)
for (p in plist){
  parts_output <- paste(args[2],'/',parts_output_basename, "_" , p, ".pdf", sep="")
  ggsave(parts_output, plot = print_parts_codelines(parts_data, codelines_data, p), width = w, height = h)
}
p<-inflex_p(qualities_data)
parts_output <- paste(args[2],'/',parts_output_basename, "_main_inflex", ".pdf", sep="")
ggsave(parts_output, plot = print_parts_codelines(parts_data, codelines_data, p), width = w, height = h)
p<-inflex2_p(qualities_data)
parts_output <- paste(args[2],'/',parts_output_basename, "_local_inflex", ".pdf", sep="")
ggsave(parts_output, plot = print_parts_codelines(parts_data, codelines_data, p), width = w, height = h)
parts_output <- paste(args[2],'/',parts_output_basename, "_details", ".pdf", sep="")
ggsave(parts_output, plot = print_details(details_data, p), width = w*2, height = h*2)
#warnings()

