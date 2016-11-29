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
library(grid)
library(gridExtra)
library(digest)
#Sys.setlocale("LC_MESSAGES", 'en_US')
options(error = quote({dump.frames(to.file=TRUE); q()}))

coeff_h=0.5
coeff_w_text=0.083

cheader_profiling<-c("Function", "Counter", "Value", "Duration", "Regions")

read <- function(file, cheader, sep=',') {
  df <- read.csv(file, header=FALSE, sep = sep, strip.white=TRUE)
  names(df) <- cheader
  df
}

make_counterlist <- function(data){
  counterlist<-data[["Counter"]]
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

print_mid <- function(data, counter){
  plot<-ggplot(data=data)
  plot<-plot+geom_text(aes(x=1,y=Function,label=Label))
  #plot<-plot+geom_segment(aes(x=0.935,xend=0.940,yend=Function))
  #plot<-plot+geom_segment(aes(x=1.06,xend=1.065,yend=Function))
  plot<-plot+ggtitle("")
  plot<-plot+ylab(NULL)
 # plot<-plot+scale_x_continuous(expand=c(0,0),limits=c(0.940,1.060))
  plot<-plot+theme(axis.title=element_blank(),panel.grid=element_blank(),axis.text.y=element_blank(),axis.ticks.y=element_blank(),panel.background=element_blank(),axis.text.x=element_text(color=NA, size=3),axis.ticks.x=element_line(color=NA),plot.margin = unit(c(1,-1,1,-1), "mm"))
  plot
}

print_duration <- function(data, counter){
  plot<-ggplot(data=data, aes(x = Function, y = Duration, fill = Duration))
  plot<-plot+geom_bar(stat = "identity")
  plot<-plot+ggtitle("Duration (ms)")
  plot<-plot+theme(axis.title.x = element_blank(),axis.title.y = element_blank(),axis.text.y = element_blank(),axis.ticks.y = element_blank(),plot.margin = unit(c(1,-1,1,0), "mm"))
  plot<-plot+scale_y_reverse()
  plot<-plot+coord_flip()
  plot<-plot+scale_fill_gradient2(low = "red", mid = "gold", high = "green3", midpoint = mean(dtemp$Duration), na.value = "grey50")
  plot<-plot + guides(fill=FALSE)
  plot
}

print_value <- function(data, counter, correlation){
  plot<-ggplot(data=data, aes(x = Function, y = Value, fill = Value))
  plot<-plot+xlab(NULL)
  plot<-plot+geom_bar(stat = "identity")
  title=paste(counter, "/s")
  plot<-plot+ggtitle(title)
  plot<-plot+theme(axis.title.x = element_blank(), axis.title.y = element_blank(),axis.text.y = element_blank(), axis.ticks.y = element_blank(),plot.margin = unit(c(1,0,1,-1), "mm"))
  plot<-plot+coord_flip()
  if (is.na(correlation)|correlation>=0){
    high=as.character("green3")
    low=as.character("red")
  }else{
    high=as.character("red")
    low=as.character("green3")
  }
  plot<-plot+scale_fill_gradient2(low = low, mid = "gold", high = high, midpoint = mean(dtemp$Value), na.value = "grey50")
  plot<-plot + guides(fill=FALSE)
  plot
}

#MAIN

#managing the arguments
args <- commandArgs(trailingOnly = TRUE)
arg_input_directory=args[1]
arg_output_directory=args[2]
set_size=as.integer(args[3])
w=as.integer(args[4])
h=as.integer(args[5])
d=as.integer(args[6])
#retrieving the input files
input=list.files(arg_input_directory, pattern="\\.profiling\\.csv$")
input_file <- paste(arg_input_directory,'/',input[1], sep="")
#reading
data <-read(input_file, cheader_profiling, ';')
#determining the counterlist
counterlist<-make_counterlist(data)
#selecting PAPI_TOT_INS as reference to determine how to apply the color gradient: red=bad, green=good
#ex: low MIPS=bad=red but low cache misses=good=green
#principle: compute the correlation between PAPI_TOT_INS and the current counter: if positive, keep same gradient, else, invert it
dref<-data[(data$Counter %in% "PAPI_TOT_INS"),]
correlate=FALSE
if (nrow(dref)>0){
  correlate=TRUE
  dref$Function <- factor(dref$Function, levels = dref[order(dref$Duration),"Function"])
  dref=dref[order(dref$Duration),]
}
#for each counter, print the profiling view
for (counter in counterlist){
  c_value=0
  dtemp<-data[(data$Counter %in% counter),]
  dtemp$Function <- factor(dtemp$Function, levels = dtemp[order(dtemp$Duration),"Function"])
  #sort routines by duration
  dtemp=dtemp[order(dtemp$Duration),]
  #compute the correlation
  if (correlate){
    c_value= cor(dtemp$Value, dref$Value)
    c=paste("Correlation: PAPI_TOT_INS vs",counter,"=",c_value)
  }
  #manage the size of each column + the size of the height
  if (set_size>0){
    dtemp=dtemp[(nrow(dtemp)-set_size):nrow(dtemp),]
    h=set_size*coeff_h
  }else{
    set_size2=49.0/coeff_h
    if (set_size2>nrow(dtemp)){
      h=nrow(dtemp)*coeff_h
    }else{
      dtemp=dtemp[(nrow(dtemp)-set_size2):nrow(dtemp),]
      h=set_size2*coeff_h
    }
  }
  w=0
  #processing the label, removing "Cluster_" to gain room
  dtemp$Regions=gsub("Cluster_", "", dtemp$Regions)
  dtemp$Label=paste(dtemp$Function, " (", dtemp$Regions, ")", sep="")
  for (funct in unique(dtemp$Label)){
    w_temp=nchar(as.character(funct))*coeff_w_text*3.0
    if (w_temp>w){
      w=w_temp
    }
  }
  if (w>=50){
    w=49
  }
  #build duration histogram
  plot1=print_duration(dtemp, counter)
  #build column center with routine names
  plot2=print_mid(dtemp, counter)
  #build performance value histogram
  plot3=print_value(dtemp, counter,c_value)
  #merge the three histograms
  g <- arrangeGrob(plot1, plot2, plot3, ncol=3, widths=c(1/3,1/3,1/3)) #generates g
  output <- paste(arg_output_directory,'/',counter,".pdf", sep="")
  ggsave(output, g, width = w, height = h, dpi=d)
}
#warnings()

