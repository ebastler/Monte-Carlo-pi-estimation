#Read the log file from the c program
data <- read.csv(file="pi.log", header=F)
#A sufficiently precise known literature value of pi to be added as a comparison 
piLit <- 3.14159265359


#Assign separate variables for sample count and pi values
sampleCount <- data$V1
pi <- data$V2


#Two plots above each other, low vertical margins in between
par(mfrow=c(2,1),
    oma = c(4,0,3,0) + 0.1,
    mar = c(0,4,0,0) + 0.1
)

#Plot the points from the log file, x axis = number of samples, y axis = value of pi
plot(sampleCount,pi,
     ylab = "Value of pi",
     xlab = NA,
     cex = .6,
     xaxt = "n"
)
#Add the literature value for reference
abline(h=piLit,
       lty = "dashed",
       col = "red"
)
#Add a legend with both values
legend("topright",
       lty = c(NA,"dashed"),
       col = c("black", "red"),
       pch = c(1,NA),
       c(paste("Point samples. Final value: ", pi[length(pi)]), paste("Literature value: ", piLit))
)


#Plot the relative error in %
plot(sampleCount, (100*abs(pi-piLit)/piLit),
     ylab = "Relative error in %",
     cex = 0.6
)


#Add the main title above
title(main = "Estimation of pi using the Monte Carlo method",
      line = 1,
      outer = TRUE
)


#Add the x axis label below
title(xlab = "Number of point samples",
      line = 2,
      outer = TRUE
)