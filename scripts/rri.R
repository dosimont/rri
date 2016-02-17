library(ggplot2)
Sys.setlocale("LC_MESSAGES", 'en_US')

h <- 6
w <- 12

parts_input_file="partitions.csv"
qualities_input_file="qualities.csv"
parts_output_file="parts"
qualities_output_file="qualities.pdf"

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
  plist<-unique(plist)
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
  plot<-plot + scale_colour_manual(name="Quality measures",values = c("green","red"))
  plot
}

print_parts <- function(data, p){
  dtemp<-data[(data$P %in% p),]
  xlabel<-  paste("Time (relative), p=", p, sep="")
  legend<-  paste("Relevant routines, p=", p, sep="")
  plot<-ggplot()
  plot<-plot+scale_x_continuous(name=xlabel)
  plot<-plot+geom_rect(data=dtemp, mapping=aes(xmin=START, xmax=END, fill=COLOR), color="black", ymin=0, ymax=1)
  plot<-plot + theme_bw()
  plot
}

args <- commandArgs(trailingOnly = TRUE)
qualities_input <- paste(args[1],'/',qualities_input_file, sep="")
qualities_data <-read_qualities(qualities_input)
qualities_output <- paste(args[2],'/',qualities_output_file, sep="")
ggsave(qualities_output, plot = print_qualities(qualities_data), width = w, height = h)
parts_input <- paste(args[1],'/',parts_input_file, sep="")
parts_data <-read_parts(parts_input)
plist<-make_plist(parts_data)
for (p in plist){
  parts_output <- paste(args[2],'/',parts_output_file, "_" , p, ".pdf", sep="")
  ggsave(parts_output, plot = print_parts(parts_data, p), width = w, height = h)
}
warnings()

