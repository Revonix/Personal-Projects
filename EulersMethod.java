//////////////////////////////////////////////////////////////
//Project Name: Eulers Method
//Project Type: Eclipse Java File
//Author: Ryan Vong
//



import java.util.*;
import java.math.BigDecimal;

public class EulersMethod {
	public static void main (String args[]) {
		
		//Creating a Scanner to take user input
		Scanner input = new Scanner(System.in);
		
		BigDecimal stepsize = new BigDecimal("0.0");
		BigDecimal initialX = new BigDecimal("0.0");
		BigDecimal initialY = new BigDecimal("0.0");
		BigDecimal maximumX = new BigDecimal("0.0");
		
		//Derivative information
		String derivative = "";
		
		//Asking for user input
		System.out.println("Eulers Method Calculator v1.0.0");
		System.out.println("A Calculator that displays the Eulers Method and its calculations.\n");
		
		System.out.println("What is the stepsize? (dx, change in x)");
		stepsize = input.nextBigDecimal();
		
		System.out.println("What is the initial value of X?");
		initialX = input.nextBigDecimal();
		
		System.out.println("What is the initial value of Y?");
		initialY = input.nextBigDecimal();
		
		System.out.println("What value of X do you want to add up to?");
		maximumX = input.nextBigDecimal();
	
		System.out.println("Type the derivative. Format ex. 6x^2");
		input.nextLine();
		derivative = input.nextLine();
		
		//Creating derivative object
		Monomial deriv = new Monomial(derivative);
		
		displayTable(stepsize, deriv, initialX, initialY, maximumX);
		
	}
	
	public static void displayTable(BigDecimal step, Monomial derivative, BigDecimal x, BigDecimal y, BigDecimal mX)
	{
		System.out.println("\nStepsize: " + step);
		System.out.println("Initial value: y(" + x + ") = " + y);
		System.out.println("Derivative/Slope: " + derivative.displayMonomial());
	
		tableLine(step, derivative, x, y, mX);
		
		
	}
	
	//Method that prints each individual line, recursively calling itself again
	public static void tableLine(BigDecimal step, Monomial derivative, BigDecimal x, BigDecimal y, BigDecimal maxX)
	{
		BigDecimal newX = x.add(step);
		BigDecimal newY = y.add(derivative.calculateDerivative(x).multiply(step));
		
		//Printing the line
		System.out.println("(" + x + ", " + y + ") | " + x + " + " + step + " | " + y + " + " + derivative.displayMonomial() + " * " + step + "| (" + newX + ", " + newY + ")");
		
		if (newX.compareTo(maxX) < 0)
			tableLine(step, derivative, newX, newY, maxX);
		else
			System.out.println("\nThe value of Y at X = " + newX + " is y(" + newX + ") = " + newY);
	}
}
