library(neuralnet)
data <- read.csv("lynxhare.csv")

data$Year <- 0:90/90

nn <- neuralnet(Hare ~ Year, data, 10, linear.output=T, act.fct=function(x) x)
pred <- predict(nn, data)
plot(data$Year, data$Hare, "l")
lines(data$Year, pred, col=2)