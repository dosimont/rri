library(ggplot2)
Sys.setlocale("LC_MESSAGES", 'en_US')

h <- 6
w <- 12

parts_input_file="partitions.csv"
qualities_input_file="qualities.csv"
codelines_input_file="codelines.csv"
parts_output_basename="parts"
qualities_output_file="qualities.pdf"
qualities2_output_file="qualities2.pdf"

cheader_parts<-c("P", "START", "END", "Function")
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

best_p <- function(data){
  dtemp<-data
  #dtemp<-dtemp[(dtemp$LOSS<0.25),]
  dtemp$SLOPE<-rep(0, nrow(dtemp))
  dtemp$SLOPESLOPE<-rep(0, nrow(dtemp))
  for (i in 2:nrow(dtemp)){
    dtemp[i,"SLOPE"]<-(dtemp[i,"GAIN"]-dtemp[i-1,"GAIN"])/(dtemp[i,"LOSS"]-dtemp[i-1,"LOSS"])
    dtemp[i,"SLOPESLOPE"]<-(dtemp[i,"SLOPE"]-dtemp[i-1,"SLOPE"])/(dtemp[i,"LOSS"]-dtemp[i-1,"LOSS"])
  }
  i<-which.max(dtemp[,"SLOPESLOPE"])
  dtemp[i[1]-1,"P"]
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
  dtemp$SLOPE<-rep(0, nrow(dtemp))
  dtemp$SLOPESLOPE<-rep(0, nrow(dtemp))
  for (i in 2:nrow(dtemp)){
    dtemp[i,"SLOPE"]<-(dtemp[i,"GAIN"]-dtemp[i-1,"GAIN"])/(dtemp[i,"LOSS"]-dtemp[i-1,"LOSS"])
    dtemp[i,"SLOPESLOPE"]<-(dtemp[i,"SLOPE"]-dtemp[i-1,"SLOPE"])/(dtemp[i,"LOSS"]-dtemp[i-1,"LOSS"])
  }
  SLOPE_MAX=max(dtemp$SLOPE, na.rm = TRUE)
  SLOPESLOPE_MAX=max(dtemp$SLOPESLOPE, na.rm = TRUE)
  dtemp$SLOPE=dtemp$SLOPE/SLOPE_MAX
  dtemp$SLOPESLOPE=dtemp$SLOPESLOPE/SLOPESLOPE_MAX
  xlabel<- "Complexity reduction"
  ylabel<- "Information loss"
  plot<-ggplot(dtemp, aes(LOSS))
  plot<-plot+geom_line(aes(y=GAIN, color = "curve"))
  plot<-plot+geom_point(aes(y=GAIN, color = "curve"))
  plot<-plot+geom_line(aes(y=SLOPE, color = "slope"))
  plot<-plot+geom_point(aes(y=SLOPE, color = "slope"))
  plot<-plot+geom_line(aes(y=SLOPESLOPE, color = "slope2"))
  plot<-plot+geom_point(aes(y=SLOPESLOPE, color = "slope2"))
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
  plot<-plot + theme_bw()
  plot
}

print_parts_codelines <- function(parts_data, codelines_data, p){
  parts_temp<-parts_data[(parts_data$P %in% p),]
  codelines_temp<-codelines_data[(codelines_data$P %in% p),]
  xlabel<-paste("Time (relative), p=", p, sep="")
  legend<-paste("Relevant routines, p=", p, sep="")
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel)
  plot<-plot+scale_y_reverse()
  plot<-plot+geom_rect(data=parts_temp, mapping=aes(xmin=START, xmax=END, fill=Function), color="white", ymin=-Inf, ymax=Inf)
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
codelines_input <- paste(args[1],'/',codelines_input_file, sep="")
parts_data <-read(parts_input, cheader_parts)
codelines_data <-read(codelines_input, cheader_codelines)
plist<-make_plist(parts_data)
for (p in plist){
  parts_output <- paste(args[2],'/',parts_output_basename, "_" , p, ".pdf", sep="")
  ggsave(parts_output, plot = print_parts_codelines(parts_data, codelines_data, p), width = w, height = h)
}
p<-best_p(qualities_data)
  parts_output <- paste(args[2],'/',parts_output_basename, "_best", ".pdf", sep="")
  ggsave(parts_output, plot = print_parts_codelines(parts_data, codelines_data, p), width = w, height = h)

warnings()

