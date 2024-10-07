library(neuralnet)
library(rioja)
data <- read.csv("rotiferflagellatealgae.csv")

data$Rotdif = c(data$Rotifer[2] - data$Rotifer[1], data$Rotifer[3:30] - data$Rotifer[1:28], data$Rotifer[30] - data$Rotifer[29]) / data$Rotifer
data$Fladif = c(data$Flagellate[2] - data$Flagellate[1], data$Flagellate[3:30] - data$Flagellate[1:28], data$Flagellate[30] - data$Flagellate[29]) / data$Flagellate
data$Algdif = c(data$Algae[2] - data$Algae[1], data$Algae[3:30] - data$Algae[1:28], data$Algae[30] - data$Algae[29]) / data$Algae

actfunc = function(x) x

rnet <- neuralnet(Rotdif ~ Rotifer + Flagellate + Algae, data, 10, linear.output=T, act.fct=actfunc)
fnet <- neuralnet(Fladif ~ Rotifer + Flagellate + Algae, data, 10, linear.output=T, act.fct=actfunc)
anet <- neuralnet(Algdif ~ Rotifer + Flagellate + Algae, data, 10, linear.output=T, act.fct=actfunc)

interdata <- as.data.frame(interp.dataset(data, 0:29*2, 0:5800/100, method="sspline"))

rpred = predict(rnet, interdata)
fpred = predict(fnet, interdata)
apred = predict(anet, interdata)

par(mfrow=c(2,3))

plot(data$Time, data$Rotdif, pch = 16, xlab="", ylab="Per Capita Growth Rate", main="Rotifer")
abline(0, 0, lty=3, lwd=2)
lines(interdata$Time, rpred, col=2, lwd = 3)

plot(data$Time, data$Fladif, pch = 16, xlab="", ylab="", main="Flagellate")
abline(0, 0, lty=3, lwd=2)
lines(interdata$Time, fpred, col=4, lwd = 3)

plot(data$Time, data$Algdif, pch = 16, xlab="", ylab="", main="Algae")
abline(0, 0, lty=3, lwd=2)
lines(interdata$Time, apred, col=3, lwd = 3)

interdata$Rotifer = interdata$Rotifer + 0.1
reffr = predict(rnet, interdata) - rpred
feffr = predict(fnet, interdata) - fpred
aeffr = predict(anet, interdata) - apred
interdata$Rotifer = interdata$Rotifer - 0.1

interdata$Flagellate = interdata$Flagellate + 0.1
refff = predict(rnet, interdata) - rpred
fefff = predict(fnet, interdata) - fpred
aefff = predict(anet, interdata) - apred
interdata$Flagellate = interdata$Flagellate - 0.1

interdata$Algae = interdata$Algae + 0.1
reffa = predict(rnet, interdata) - rpred
feffa = predict(fnet, interdata) - fpred
aeffa = predict(anet, interdata) - apred
interdata$Algae = interdata$Algae - 0.1

plot(interdata$Time, reffr, "l", col=2, lwd=3, ylim=c(-0.5,0.5), xlab="Time", ylab="")
lines(interdata$Time, refff, col=4, lwd=3)
lines(interdata$Time, reffa, col=3, lwd=3)

plot(interdata$Time, feffr, "l", col=2, lwd=3, ylim=c(-0.5,0.5), xlab="Time", ylab="")
lines(interdata$Time, fefff, col=4, lwd=3)
lines(interdata$Time, feffa, col=3, lwd=3)

plot(interdata$Time, aeffr, "l", col=2, lwd=3, ylim=c(-0.5,0.5), xlab="Time", ylab="")
lines(interdata$Time, aefff, col=4, lwd=3)
lines(interdata$Time, aeffa, col=3, lwd=3)

#plot(interdata$Time, reffr*interdata$Rotifer, "l", col=2, lwd=3, ylim=c(-0.5,0.5), xlab="", ylab="")
#lines(interdata$Time, refff*interdata$Flagellate, col=4, lwd=3)
#lines(interdata$Time, reffa*interdata$Algae, col=3, lwd=3)

#plot(interdata$Time, feffr*interdata$Rotifer, "l", col=2, lwd=3, ylim=c(-1,1), xlab="", ylab="")
#lines(interdata$Time, fefff*interdata$Flagellate, col=4, lwd=3)
#lines(interdata$Time, feffa*interdata$Algae, col=3, lwd=3)

#plot(interdata$Time, aeffr*interdata$Rotifer, "l", col=2, lwd=3, ylim=c(-0.5,0.5), xlab="", ylab="")
#lines(interdata$Time, aefff*interdata$Flagellate, col=4, lwd=3)
#lines(interdata$Time, aeffa*interdata$Algae, col=3, lwd=3)