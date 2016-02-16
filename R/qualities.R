library(ggplot2)
Sys.setlocale("LC_MESSAGES", 'en')

h <- 6
w <- 12

inputfile="qualities.csv"
outputfile="qualities.pdf"

cheader<-c("P", "GAIN", "LOSS")

read_data <- function(file) {
  df <- read.csv(file, header=FALSE, sep = ",", strip.white=TRUE)
  names(df) <- cheader
  df
}

print <- function(data){
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
plot<-plot + scale_colour_manual(name="Mesures de qualité",values = c("red","green"))
plot
}


args <- commandArgs(trailingOnly = TRUE)
input <- paste(args[1],'/',inputfile, sep="")
data <- read_data(input)
output <- paste(args[2],'/',outputfile, sep="")
ggsave(output, plot = print(data), width = w, height = h)

