#   RRI - Relevant Routine Identifier
#   Copyright (C) 2016  Damien Dosimont
#
#   This file is part of RRI.
#
#   RRI is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.


library(ggplot2)
library(RColorBrewer)
library(gridExtra)
library(digest)
#Sys.setlocale("LC_MESSAGES", 'en_US')

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
cheader_dump<-c("TYPE", "INSTANCE", "GROUP", "TS", "COUNTER", "VALUE")
cheader_interpolate<-c("INSTANCE", "GROUP", "COUNTER", "TS", "VALUE")
cheader_slope<-c("INSTANCE", "GROUP", "COUNTER", "TS", "VALUE", "CUMUL")

read <- function(file, cheader, sep=',') {
  df <- read.csv(file, header=FALSE, sep = sep, strip.white=TRUE)
  names(df) <- cheader
  df
}

make_plist <- function(data){
  plist<-data[["P"]]
  plist<-unique(plist)
  plist
}

make_counterlist <- function(data){
  counterlist<-data[["COUNTER"]]
  counterlist<-unique(counterlist)
  counterlist
}

string2color<- function(string){
  digested=digest(as.character(string), serialize=FALSE)
  r=substr(digested,1,2)
  g=substr(digested,3,4)
  b=substr(digested,5,6)
  h<-paste(r,g,b,sep="")
  if ((r>200&g>200&b>200)|(r<50&g<50&b<50)){
    h = string2color(paste(string,":270:Republique",sep=""))
  }
  h
}

color_generator <- function(stringlist, aggString=c("")){
  sorted<-sort(stringlist)
  hashcoded<-rep(0, length(stringlist))
  for (i in 1:length(sorted)){
    if (sorted[i]==aggString){
      hashcoded[i]=0
    }
    else{
      hashcoded[i]=string2color(sorted[i])
    }
  }
  hexed<-format(as.hexmode(hashcoded),width=6)
  color=paste("#",hexed,sep="")
  names(color)=sorted
  color
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

print_details <- function(data, p, jesus){
  dtemp<-data[(data$P %in% p),]
  dtemp<-dtemp[!(dtemp$Function %in% "void"),]
  dtemp<-dtemp[order(dtemp$START, -dtemp$Callstack), ]
  callstackDepth<-dtemp[which.max(dtemp[,"Callstack"]),"Callstack"]
  for (i in 0:callstackDepth){
    func<-unique(dtemp[(dtemp$Callstack %in% i),"Function"])
    fv<-seq(1,length(func))
    names(fv)<-func
    dtemp[(dtemp$Callstack %in% i),"POSITION"]<-fv[dtemp[(dtemp$Callstack %in% i),"Function"]]
  }
  dtemp<-dtemp[order(dtemp$START, -dtemp$Callstack, dtemp$POSITION),]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  ylabel<-  paste("Execution time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  dtemp$OFFSET<-0
  currentStart<-dtemp[1,"START"]
  currentCallstack<-dtemp[1,"Callstack"]
  offset<-0
  for (i in 2:nrow(dtemp)){
    newStart=dtemp[i,"START"]
    newCallstack=dtemp[i,"Callstack"]
    if (newStart != currentStart){
    currentStart<-newStart
    currentCallstack=newCallstack
    offset<-0
    }else{
      if (newCallstack != currentCallstack){
      currentCallstack=newCallstack
      offset<-callstackDepth-currentCallstack
      }
      else{
      offset<-offset+dtemp[i-1,"Ratio"]
      }
      dtemp[i,"OFFSET"]<-offset
    }
  }
  dtemp<-dtemp[order(dtemp$SELECTED), ]
  dtemp2<-dtemp[(dtemp$SELECTED %in% 1), ]
  dsize=0.3
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  func<-unique(dtemp[["Function"]])
  vcolors=color_generator(func)
  if (jesus){
    plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=Function, colour=Function))
    plot<-plot+geom_rect(data=dtemp2, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=NA), color="black", size=dsize)
    plot<-plot+scale_colour_manual(values = vcolors)
  }
  else{
    plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=Function), color="white", size=dsize)
    plot<-plot+geom_rect(data=dtemp2, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=NA), color="black", size=dsize/3)
  }
  plot<-plot+scale_fill_manual(values = vcolors)
  plot<-plot + theme_bw()
  plot<-plot+ theme(legend.position="bottom")
}

print_details_aggreg <- function(data, p, jesus){
  dtemp<-data[(data$P %in% p),]
  dtemp<-dtemp[!(dtemp$Function %in% "void"),]
  callstackDepth<-dtemp[which.max(dtemp[,"Callstack"]),"Callstack"]
  aggCallstackDepth<-0
  aggVector=c()
  for (i in callstackDepth:0){
    func<-unique(dtemp[(dtemp$Callstack %in% i),"Function"])
    print(func)
    print(length(func))
    print(func[1])
    if (length(func) == 1){
      temp<-dtemp[dtemp$Function %in% func[1],]
      if (length(!(temp$Ratio %in% 1)==0)&length((temp$SELECTED %in% 1)==0)){
        temp$DURATION=temp$END-temp$START
        duration=sum(temp$DURATION)
        if (duration == 1){
          aggCallstackDepth<-callstackDepth-i+1
          print(func[1])
          aggVector[callstackDepth-i+1]=as.character(func[1])
          print(aggVector)
        }else break
      }else break
    }else break
  }
  aggString=c("")
  print(aggVector)
  if (aggCallstackDepth>=2){
    aggString=paste(aggVector,collapse="+")
    print(aggString)
    dtemp=dtemp[(dtemp$Callstack<=(callstackDepth-aggCallstackDepth+1)),]
    print(dtemp$Callstack %in% (callstackDepth-aggCallstackDepth+1))
    levels(dtemp$Function) <- c(levels(dtemp$Function), as.character(aggString))
    dtemp$Function[(dtemp$Callstack %in% (callstackDepth-aggCallstackDepth+1))]<-as.character(aggString)
  }
  print(dtemp)
  dtemp<-dtemp[order(dtemp$START, -dtemp$Callstack), ]
  callstackDepth<-dtemp[which.max(dtemp[,"Callstack"]),"Callstack"]
  for (i in 0:callstackDepth){
    func<-unique(dtemp[(dtemp$Callstack %in% i),"Function"])
    fv<-seq(1,length(func))
    names(fv)<-func
    dtemp$POSITION[(dtemp$Callstack %in% i)]<-fv[dtemp[(dtemp$Callstack %in% i),"Function"]]
  }
  dtemp<-dtemp[order(dtemp$START, -dtemp$Callstack, dtemp$POSITION),]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  ylabel<-  paste("Execution time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  dtemp$OFFSET<-0
  currentStart<-dtemp[1,"START"]
  currentCallstack<-dtemp[1,"Callstack"]
  offset<-0
  for (i in 2:nrow(dtemp)){
    newStart=dtemp[i,"START"]
    newCallstack=dtemp[i,"Callstack"]
    if (newStart != currentStart){
    currentStart<-newStart
    currentCallstack=newCallstack
    offset<-0
    }else{
      if (newCallstack != currentCallstack){
      currentCallstack=newCallstack
      offset<-callstackDepth-currentCallstack
      }
      else{
      offset<-offset+dtemp[i-1,"Ratio"]
      }
      dtemp[i,"OFFSET"]<-offset
    }
  }
  dtemp<-dtemp[order(dtemp$SELECTED), ]
  print(dtemp)
  dtemp2<-dtemp[(dtemp$SELECTED %in% 1), ]
  dsize=0.3
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  func<-unique(dtemp[["Function"]])
  vcolors=color_generator(func, as.character(aggString))
  if (jesus){
    plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=Function, colour=Function))
    plot<-plot+geom_rect(data=dtemp2, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=NA), color="black", size=dsize)
    plot<-plot+scale_colour_manual(values = vcolors)
  }
  else{
    plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=Function), color="white", size=dsize)
    plot<-plot+geom_rect(data=dtemp2, mapping=aes(xmin=START, xmax=END, ymin=OFFSET, ymax=OFFSET+Ratio, fill=NA), color="black", size=dsize/3)
  }
  plot<-plot+scale_fill_manual(values = vcolors)
  plot<-plot + theme_bw()
  plot<-plot+ theme(legend.position="bottom")
}

print_parts_codelines <- function(parts_data, codelines_data, p){
  parts_temp<-parts_data[(parts_data$P %in% p),]
  parts_temp<-parts_temp[!(parts_temp$Function %in% "void"),]
  codelines_temp<-codelines_data[(codelines_data$P %in% p),]
  xlabel<-paste("Time (relative), p=", p, sep="")
  ylabel<-"Codeline"
  title<-("Relevant Routines")
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  plot<-plot+scale_y_reverse(name=ylabel)
  plot<-plot+ggtitle(title)
  plot<-plot+geom_rect(data=parts_temp, mapping=aes(xmin=START, xmax=END, fill=Function), color="white", ymin=-Inf, ymax=Inf)
  plot<-plot+geom_point(data=codelines_temp, aes(x=TS, y=Codeline), color="black", size=0.2)
  func<-unique(parts_temp[["Function"]])
  plot<-plot+scale_fill_manual(values = color_generator(func))
  plot<-plot + theme_bw()
  plot<-plot+ theme(legend.position="bottom")
  plot
}

print_perf_counter <- function(dump_temp, interpolate_temp, slope_temp, counter){
  #Dump
  dump_temp$CUMUL<-0
  dump_temp$SAMPLES<-1
  excluded<-dump_temp[(dump_temp$TYPE %in% "e"),]
  unused<-dump_temp[(dump_temp$TYPE %in% "un"),]
  used<-dump_temp[(dump_temp$TYPE %in% "u"),]
  #Slope
  slope_max<-slope_temp[which.max(slope_temp[,"VALUE"]),"VALUE"]
  slope_temp$VALUE<-slope_temp$VALUE/slope_max
  slope_temp$TYPE<-"s"
  slope_temp$SAMPLES<-0
  #Interpolate
  sample_max<-interpolate_temp[which.max(interpolate_temp[,"VALUE"]),"VALUE"]
  interpolate_temp$VALUE<-interpolate_temp$VALUE/sample_max
  interpolate_temp$CUMUL<-0
  interpolate_temp$TYPE<-"i"
  interpolate_temp$SAMPLES<-0
  #Normalizing
  excluded$VALUE<-excluded$VALUE/sample_max
  unused$VALUE<-unused$VALUE/sample_max
  used$VALUE<-used$VALUE/sample_max
  #Merging
  total<-rbind(rbind(rbind(excluded,unused),rbind(used,slope_temp)),interpolate_temp)
  #Printing
  xlabel<-"Time (relative)"
  ylabel<-"Amplitude (normalized)"
  title<-paste(counter,"vs Time", "- Max interpolate value =", sample_max, "- Max slope value =", slope_max)
  plot<-ggplot(total, aes(x=TS,y=VALUE,colour=TYPE))
  plot<-plot+geom_point(data=total[total$SAMPLES %in% 1,])
  plot<-plot+geom_line(data=total[total$SAMPLES %in% 0,], size=1.2)
  plot<-plot+labs(y=ylabel)
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  plot<-plot+ggtitle(title)
  plot<-plot + scale_colour_manual(name="",breaks = c("i", "s", "u", "un", "e"), labels = c("e"="Excluded samples ", "i"="Interpolation ", "s"="Slope ", "u"="Used samples ", "un"="Unused samples "), values = c("i"="green", "u"="red", "un"="yellow", "e"="grey", "s"="blue"))
  plot<-plot+theme_bw()
  plot<-plot+theme(legend.position="bottom")
  plot
}

args <- commandArgs(trailingOnly = TRUE)
arg_perf_directory=args[1]
arg_instance_directory=args[2]
arg_instance_name=args[3]
arg_output_directory=args[4]
w=as.integer(args[5])
h=as.integer(args[6])
d=as.integer(args[7])
dump_input=list.files(arg_perf_directory, pattern="\\.dump\\.csv$")
interpolate_input=list.files(arg_perf_directory, pattern="\\.interpolate\\.csv$")
slope_input=list.files(arg_perf_directory, pattern="\\.slope\\.csv$")
dump_input <- paste(arg_perf_directory,'/',dump_input[1], sep="")
interpolate_input <- paste(arg_perf_directory,'/',interpolate_input[1], sep="")
slope_input <- paste(arg_perf_directory,'/',slope_input[1], sep="")
dump_data <-read(dump_input, cheader_dump, ';')
interpolate_data <-read(interpolate_input, cheader_interpolate, ';')
slope_data <-read(slope_input, cheader_slope, ';')
qualities_input <- paste(arg_instance_directory,'/',qualities_input_file, sep="")
qualities_data <-read(qualities_input, cheader_qualities)
qualities_output <- paste(arg_output_directory,'/',qualities_output_file, sep="")
ggsave(qualities_output, plot = print_qualities(qualities_data), width = w, height = h, dpi=d)
qualities2_output <- paste(arg_output_directory,'/',qualities2_output_file, sep="")
ggsave(qualities2_output, plot = print_qualities2(qualities_data), width = w, height = h, dpi=d)
parts_input <- paste(arg_instance_directory,'/',parts_input_file, sep="")
details_input <- paste(arg_instance_directory,'/',details_input_file, sep="")
codelines_input <- paste(arg_instance_directory,'/',codelines_input_file, sep="")
parts_data <-read(parts_input, cheader_parts)
details_data <-read(details_input, cheader_details)
codelines_data <-read(codelines_input, cheader_codelines)
plist<-make_plist(parts_data)
for (p in plist){
  parts_output <- paste(arg_output_directory,'/.',parts_output_basename, "_" , p, ".pdf", sep="")
  ggsave(parts_output, plot=print_parts_codelines(parts_data, codelines_data, p), width = w, height = h, dpi=d)
}
p<-inflex_p(qualities_data)
parts_output <- paste(arg_output_directory,'/',parts_output_basename, "_main_inflex", ".pdf", sep="")
ggsave(parts_output, print_parts_codelines(parts_data, codelines_data, p), width = w, height = h, dpi=d)
p<-inflex2_p(qualities_data)
parts_output <- paste(arg_output_directory,'/',parts_output_basename, "_local_inflex", ".pdf", sep="")
ggsave(parts_output, print_parts_codelines(parts_data, codelines_data, p), width = w, height = h, dpi=d)
parts_output <- paste(arg_output_directory,'/',parts_output_basename, "_details", ".pdf", sep="")
ggsave(parts_output, plot = print_details_aggreg(details_data, p, FALSE), width = w*2, height = h*2, dpi=d)
parts_output <- paste(arg_output_directory,'/',parts_output_basename, "_jesus", ".pdf", sep="")
ggsave(parts_output, plot = print_details_aggreg(details_data, p, TRUE), width = w*2, height = h*2, dpi=d)
plot1=print_parts_codelines(parts_data, codelines_data, p)
instance=arg_instance_name
interpolate_data<-interpolate_data[(interpolate_data$INSTANCE %in% instance),]
slope_data<-slope_data[(slope_data$INSTANCE %in% instance),]
dump_data<-dump_data[(dump_data$INSTANCE %in% instance),]
print("Discarded counters:")
test_data=interpolate_data
discarded_counter=unique(test_data[!(is.finite(test_data$VALUE)),"COUNTER"])
print(discarded_counter)
if (length(discarded_counter)!=0){
  test_data<-test_data[(is.finite(test_data$VALUE)),]
}
counterlist<-make_counterlist(test_data)
for (counter in counterlist){
  print(counter)
  dump_temp<-dump_data[(dump_data$COUNTER %in% counter),]
  slope_temp<-slope_data[(slope_data$COUNTER %in% counter),]
  interpolate_temp<-interpolate_data[(interpolate_data$COUNTER %in% counter),]
  if (nrow(dump_temp)==0 | nrow(slope_temp)==0 | nrow(interpolate_temp)==0){
    print("Invalid data, passing")
  }
  else{
    plot2=print_perf_counter(dump_temp, interpolate_temp, slope_temp, counter)
    g <- arrangeGrob(plot1, plot2, nrow=2, heights=c(1/3,2/3)) #generates g
    parts_output <- paste(arg_output_directory,'/',parts_output_basename,"_",counter,".pdf", sep="")
    ggsave(parts_output, g, width = w, height = h*2, dpi=d)
  }
}
#warnings()

