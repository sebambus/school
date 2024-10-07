orig <- read.csv("lynxhare.csv");
gen <- read.csv("modlynxhare.csv");

plot(orig$Year,orig$Hare, "l", col = 2, xlab="Year", ylab="Population");
lines(orig$Year,orig$Lynx, col = 3);

lines(gen$Year,gen$Hare, col = 2, lty = 2);
lines(gen$Year,gen$Lynx, col = 3, lty = 2);

legend(1910, 150, legend=c("Hare", "Lynx", "Hare Approx.", "Lynx Approx."), col=c(2,3,2,3), lty=c(1,1,2,2))