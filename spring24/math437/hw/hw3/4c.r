library(deSolve)

N <- 1000
gam <- 1/4

initial <- c(S = N - 1, I = 1)
times <- 1:2500 / 100

step <- function(t, y, parms) list(c(-1*parms[1]*y[1]*y[2], parms[1]*y[1]*y[2] - parms[2]*y[2]))

plot(1, type="n", xlim = c(0, 25), ylim = c(0, 1000), xlab="Time (days)", ylab="Infected Individuals")
grid(col=1)
bet = c(0.003, 0.005, 0.0125)
for(i in 1:3) {
	parms <- c(bet[i], gam)
	out <- as.data.frame(ode(initial, times, step, parms))
       	lines(out$time, out$I, "l", col = i+1, lw = 2)
	ymax <- max(out$I)
	xmax <- out$time[which.max(out$I)]
	points(xmax, ymax, pch = 21, col = i+1)
	text(xmax + 1.5, ymax + 20, labels=paste0("(", round(xmax, 1), ", ", round(ymax), ")"))
}
legend(18, 1000, c("beta=0.003", "beta=0.005", "beta=0.0125"), fill = 2:4, bg = 8)
