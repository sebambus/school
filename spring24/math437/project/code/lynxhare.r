library(neuralnet)
library(rioja)
data <- read.csv("lynxhare.csv")

data$Haredif = c(data$Hare[2] - data$Hare[1], data$Hare[3:91] - data$Hare[1:89], data$Hare[91] - data$Hare[90]) / data$Hare
data$Lynxdif = c(data$Lynx[2] - data$Lynx[1], data$Lynx[3:91] - data$Lynx[1:89], data$Lynx[91] - data$Lynx[90]) / data$Lynx

hnet <- neuralnet(Haredif ~ Hare + Lynx, data, 10, linear.output=T, act.fct=function(x) x)
lnet <- neuralnet(Lynxdif ~ Hare + Lynx, data, 10, linear.output=T, act.fct=function(x) x)

interdata <- as.data.frame(interp.dataset(data, 1845:1935, 184500:193500/100, method="sspline"))

hpred = predict(hnet, interdata)
lpred = predict(lnet, interdata)

par(mfrow=c(2,2))

plot(data$Year, data$Haredif, pch = 16, ylim = c(-10,10), xlab="Time", ylab="Per Capita Growth Rate")
abline(0, 0, lty=3, lwd=2)
lines(interdata$Year, hpred, col=2, lwd = 3)

plot(data$Year, data$Lynxdif, pch = 16, ylim = c(-3,3), xlab="Time", ylab="Per Capita Growth Rate")
abline(0, 0, lty=3, lwd=2)
lines(interdata$Year, lpred, col=4, lwd = 3)

interdata$Hare = interdata$Hare + 0.1
heffh = predict(hnet, interdata) - hpred
leffh = predict(lnet, interdata) - lpred
interdata$Hare = interdata$Hare - 0.1

interdata$Lynx = interdata$Lynx + 0.1
heffl = predict(hnet, interdata) - hpred
leffl = predict(lnet, interdata) - lpred
interdata$Lynx = interdata$Lynx - 0.1

plot(interdata$Year, heffh, "l", col=2, lwd=3, ylim=c(-0.01,0.01), xlab="", ylab="")
lines(interdata$Year, leffh, col=4, lwd=3)

plot(interdata$Year, heffl, "l", col=2, lwd=3, ylim=c(-0.01,0.01), xlab="", ylab="")
lines(interdata$Year, leffl, col=4, lwd=3)