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

parts_output_basename="folding"
cheader_parts<-c("START", "END", "Function")
cheader_dump<-c("TYPE", "INSTANCE", "GROUP", "TS", "COUNTER", "VALUE")
cheader_codelines<-c("TYPE", "INSTANCE", "GROUP", "TS", "LINE", "FUNC")
cheader_interpolate<-c("INSTANCE", "GROUP", "COUNTER", "TS", "VALUE")
cheader_slope<-c("INSTANCE", "GROUP", "COUNTER", "TS", "VALUE", "CUMUL")

labelmax=22
ulabelmax=33

read <- function(file, cheader, sep=',') {
  df <- read.csv(file, header=FALSE, sep = sep, strip.white=TRUE)
  names(df) <- cheader
  df
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
  if ((r>215&g>215&b>215)|(r<30&g<30&b<30)){
    h = string2color(paste(string,":-o",sep=""))
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

print_parts_codelines <- function(parts_data, codelines_data, instance){
  dtemp<-parts_data
  codelines_temp<-codelines_data
  codelines_temp<-codelines_temp[(codelines_temp$TYPE %in% "cl"),]
  codelines_temp<-codelines_temp[(codelines_temp$INSTANCE %in% instance),]
  codelines_temp$VALUE<-as.numeric(as.character(codelines_temp$LINE))
  xlabel<-"Time (relative)"
  ylabel<-"Codeline"
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  plot<-plot+scale_y_reverse(name=ylabel)
  plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, fill=Function), color="white", ymin=-Inf, ymax=Inf)
  plot<-plot+geom_point(data=codelines_temp, aes(x=TS, y=VALUE), color="black", size=0.2)
  func<-unique(dtemp[["Function"]])
  vcolors=color_generator(func)
  dtemp$LABEL=as.character(dtemp$Function)
  dtemp$TLABELtemp=as.character(substr(dtemp$LABEL,1,labelmax))
  dtemp$TLABELtemp=as.character(paste(dtemp$TLABELtemp,"...",sep=""))
  dtemp$TLABEL=as.character(dtemp$Function)
  dtemp[nchar(as.character(dtemp$LABEL))>labelmax,"TLABEL"]=as.character(dtemp[nchar(as.character(dtemp$LABEL))>labelmax, "TLABELtemp"])
  dtemp$ULABELtemp1=as.character(substr(dtemp$LABEL,1,ulabelmax/2-2))
  dtemp$ULABELtemp2=as.character(substr(dtemp$LABEL,nchar(as.character(dtemp$LABEL))-ulabelmax/2+1,nchar(as.character(dtemp$LABEL))))
  dtemp$ULABELtemp=as.character(paste(dtemp$ULABELtemp1,"...",dtemp$ULABELtemp2,sep=""))
  dtemp$ULABEL=as.character(dtemp$Function)
  dtemp[nchar(as.character(dtemp$LABEL))>ulabelmax,"ULABEL"]=as.character(dtemp[nchar(as.character(dtemp$LABEL))>ulabelmax, "ULABELtemp"])
  dtemp$LABEL=dtemp$ULABEL
  dtemp$VSLABEL=as.character(dtemp$Function)
  dtemp$VSLABEL=as.character(substr(dtemp$VSLABEL,1,4))
  police_size=10
  if (length(func)<15){
    police_size=9
  }else if (length(func)<20){
    police_size=8
  }else if (length(func)<25){
    police_size=7
  }else if (length(func)<30){
    police_size=6
  }else{
    police_size=5
  }
  names(func)=func
  vlabels<-vector(, length(func))
  names(vlabels)=func
  for (n in func){
    labeltemps=as.vector(dtemp$LABEL[dtemp$Function %in% n])
    vlabels[n]=as.character(labeltemps[1])
  }
  plot<-plot+scale_fill_manual(values = vcolors, breaks = sort(func), labels = vlabels)
  plot<-plot + theme_bw()
  plot<-plot+ theme(legend.position="bottom")
  plot<-plot + guides(color=FALSE)
  plot<-plot + theme(legend.text = element_text(size = police_size))
  plot
}

print_perf_counter_slope <- function(slope, counter){
  #Stats
  slope_max<-slope[which.max(slope[,"VALUE"]),"VALUE"]
  slope_mean<-mean(slope[["VALUE"]])
  #Printing
  xlabel<-"Time (relative)"
  ylabel<-"Amplitude"
  title<-paste(counter,"/s vs Time", "- Max =", ceiling(slope_max), "- Mean =", ceiling(slope_mean))
  plot<-ggplot(slope, aes(x=TS,y=VALUE))
  plot<-plot+geom_line(data=slope, size=1.2, color="blue")
  plot<-plot+scale_y_continuous(name=ylabel, expand =c(0,0))
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  plot<-plot+ggtitle(title)
  plot<-plot+theme_bw()
  plot
}

print_perf_counter <- function(dump, interpolate, counter){
  #Dump
  dump$SAMPLES<-1
  excluded<-dump[(dump$TYPE %in% "e"),]
  unused<-dump[(dump$TYPE %in% "un"),]
  used<-dump[(dump$TYPE %in% "u"),]
  #Interpolate
  interpolate$TYPE<-"i"
  interpolate$SAMPLES<-0
  #Merging
  total<-rbind(rbind(rbind(excluded,unused),used),interpolate)
  #Printing
  xlabel<-"Time (relative)"
  ylabel<-"Amplitude (normalized)"
  title<-paste(counter,"vs Time")
  plot<-ggplot(total, aes(x=TS,y=VALUE,colour=TYPE))
  plot<-plot+geom_point(data=total[total$SAMPLES %in% 1,])
  plot<-plot+geom_line(data=total[total$SAMPLES %in% 0,], size=1.2)
  plot<-plot+scale_y_continuous(name=ylabel, expand =c(0,0))
  plot<-plot+scale_x_continuous(name=xlabel, limits =c(0,1))
  plot<-plot+ggtitle(title)
  plot<-plot + scale_colour_manual(name="",breaks = c("i", "u", "un", "e"), labels = c("e"="Excluded samples ", "i"="Interpolation ", "u"="Used samples ", "un"="Unused samples "), values = c("i"="green", "u"="red", "un"="yellow", "e"="grey"))
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
filter=10
dump_input=list.files(arg_perf_directory, pattern="\\.dump\\.csv$")
interpolate_input=list.files(arg_perf_directory, pattern="\\.interpolate\\.csv$")
slope_input=list.files(arg_perf_directory, pattern="\\.slope\\.csv$")
dump_input <- paste(arg_perf_directory,'/',dump_input[1], sep="")
interpolate_input <- paste(arg_perf_directory,'/',interpolate_input[1], sep="")
slope_input <- paste(arg_perf_directory,'/',slope_input[1], sep="")
dump_data <-read(dump_input, cheader_dump, ';')
interpolate_data <-read(interpolate_input, cheader_interpolate, ';')
slope_data <-read(slope_input, cheader_slope, ';')
parts_input <- paste(arg_instance_directory,'/', "parts.csv", sep="")
parts_data <-read(parts_input, cheader_parts)
codelines_data <- read(dump_input, cheader_codelines, ';')
parts_output <- paste(arg_output_directory,'/',parts_output_basename, ".pdf", sep="")
ggsave(parts_output, print_parts_codelines(parts_data, codelines_data, arg_instance_name), width = w, height = h, dpi=d)
plot1=print_parts_codelines(parts_data, codelines_data, arg_instance_name)
instance=arg_instance_name
interpolate_data<-interpolate_data[(interpolate_data$INSTANCE %in% instance),]
slope_data<-slope_data[(slope_data$INSTANCE %in% instance),]
dump_data<-dump_data[(dump_data$INSTANCE %in% instance),]
#print("Discarded counters:")
test_data=interpolate_data
discarded_counter=unique(test_data[!(is.finite(test_data$VALUE)),"COUNTER"])
#print(discarded_counter)
if (length(discarded_counter)!=0){
  test_data<-test_data[(is.finite(test_data$VALUE)),]
}
counterlist<-make_counterlist(test_data)
for (counter in counterlist){
 # print(counter)
  dump_temp<-dump_data[(dump_data$COUNTER %in% counter),]
  slope_temp<-slope_data[(slope_data$COUNTER %in% counter),]
  interpolate_temp<-interpolate_data[(interpolate_data$COUNTER %in% counter),]
  if (nrow(dump_temp)==0 | nrow(slope_temp)==0 | nrow(interpolate_temp)==0){
  #  print("Invalid data, passing")
  }
  else{
    plot3=print_perf_counter_slope(slope_temp, counter)
    counters_output <- paste(arg_output_directory,"/.",counter, "_slope.pdf", sep="")
    ggsave(counters_output, plot = plot3, width = w, height = h, dpi=d)
    plot4=print_perf_counter(dump_temp, interpolate_temp, counter)
    counters_output <- paste(arg_output_directory,"/.",counter, ".pdf", sep="")
    ggsave(counters_output, plot = plot4, width = w, height = h, dpi=d)
    g <- arrangeGrob(plot1, plot3, nrow=2, heights=c(1/2,1/2)) #generates g
    parts_output <- paste(arg_output_directory,'/',parts_output_basename,"_",counter,".pdf", sep="")
    ggsave(parts_output, g, width = w, height = h*2, dpi=d)
  }
}
#warnings()

