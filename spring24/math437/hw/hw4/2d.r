library(deSolve)
library(lamW)

A_S <- 1.2
A_R <- 1
K <- 15

initials <- c(R = 0, S = 0)
times <- 1:10000/750
params <- c(As = A_S, Ar = A_R, k = K)

step <- function(time, state, pars) {
	with(as.list(c(state, pars)), {
		return(list(c(-R + As + k*S*exp(-S),
			      -S + Ar + k*R*exp(-R))))
	})
}

out <- as.data.frame(ode(initials, times, step, params))
out
plot(0, 0, "l", xlim=c(0, 12), ylim=c(0, 7), xlab="Time", ylab="Love")
legend(0, 7, c("Rhett", "Scarlett"), 2:3)
lines(out$time, out$R, col=2)
lines(out$time, out$S, col=3)
plot(out$R, out$S, "l", xlab="Rhett's Love", ylab = "Scarlett's Love", xlim=c(0, 7), ylim=c(0, 7))
legend(5, 7, c("Trajectory", "R Nullcline", "S Nullcline"), c(1,2,4))
curve(-lambertWm1(0.08 - 2/30*x), add=TRUE, col=2)
curve(-lambertW0(0.08 - 2/30*x), add=TRUE, col=2)
curve(A_R + 15*x*exp(-x), add=TRUE, col=4)
