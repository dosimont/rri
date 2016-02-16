library(ggplot2)
Sys.setlocale("LC_MESSAGES", 'en')

h <- 6
w <- 12

parts_input_file="parts.csv"
qualities_input_file="qualities.csv"
parts_output_file="parts"
qualities_output_file="parts.pdf"

cheader_parts<-c("P", "START", "END", "COLOR")
cheader_qualities<-c("P", "GAIN", "LOSS")

read_qualities <- function(file) {
  df <- read.csv(file, header=FALSE, sep = ",", strip.white=TRUE)
  names(df) <- cheader_qualities
  df
}

read_parts <- function(file) {
  df <- read.csv(file, header=FALSE, sep = ",", strip.white=TRUE)
  names(df) <- cheader_parts
  df
}

make_plist <- function(data){
  plist<-data[["P"]]
  plist
}

print_qualities <- function(data){
  dtemp<-data
  ntemp <- data.frame(P= dtemp[2:(nrow(dtemp)),1]-0.0000001, GAIN= dtemp[1:nrow(dtemp)-1,2], LOSS= dtemp[1:nrow(dtemp)-1,3])
  ntemp[1,]<-c(1,1,1)
  dtemp<-rbind(dtemp, ntemp)
  xlabel<- "Parameter p"
  ylabel<- "Amplitude (normalized)"
  legend<- "Quality Measures vs Parameter p"
  plot<-ggplot(dtemp, aes(x=P))
  plot<-plot + geom_line(aes(y=GAIN, colour = "Complexity reduction"))
  plot<-plot + geom_line(aes(y=LOSS, colour = "Information loss"))
  plot<-plot + theme_bw()
  plot<-plot + labs(x=xlabel,y=ylabel)
  plot<-plot + scale_colour_manual(name="Quality measures",values = c("red","green"))
  plot
}

print_parts <- function(data, p){
  dtemp<-data[(data$P == P)]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  plot<-ggplot(data)
  start<-dtemp[["START"]]
  end<-dtemp[["END"]]
  color<-dtemp[["COLOR"]]
  for (i in 1:length(start)){
    plot <- plot + geom_rect(xmin = start[i], xmax=end[i], ymin=0, ymax=1, fill=color[i])
  }
  plot<-plot + theme_bw()
  plot
}

args <- commandArgs(trailingOnly = TRUE)
qualities_input <- paste(args[1],'/',qualities_input_file, sep="")
qualities_data <-read_qualities(qualities_input)
qualities_output <- paste(args[2],'/',qualities_output_file, sep="")
ggsave(qualities_output, plot = print_qualities(qualities_data), width = w, height = h)
parts_input <- paste(args[1],'/',parts_input_file, sep="")
parts_data <-read_qualities(parts_input)
plist<-make_plist(qualities_data)
for (p in plist){
  print_parts(parts_data, p)
  parts_output <- paste(args[2],'/',parts_output_file, "_" , p, ".pdf", sep="")
  ggsave(parts_output, plot = print_parts(parts_data, p), width = w, height = h)
}


