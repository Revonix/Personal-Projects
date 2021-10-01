
import java.math.BigDecimal;

public class Monomial {
	private int degree;
	private int coefficent;
	
	public Monomial()
	{
		degree = 0;
		coefficent = 1;
	}
	
	//Parsing the string derivative
	public Monomial(String derivative)
	{
		degree = 0;
		coefficent = 1;
		
		//Checking for default coefficent
		if (!derivative.substring(0, 1).equalsIgnoreCase("x")) {
			//Running through each character in the string to check for the x, then backtracking to get the numbers
			for (int i = 0; i < derivative.length(); i++)
			{
				if (derivative.substring(i, i + 1).equalsIgnoreCase("x"))
				{
					coefficent = Integer.parseInt(derivative.substring(0, i));
				}
			}
		}
		
		//Running through each character in the string to check for a ^ for the exponent
		for (int i = 0; i < derivative.length(); i++)
		{
			if (derivative.substring(i, i + 1).equals("^"))
			{
				degree = Integer.parseInt(derivative.substring(i+1, derivative.length()));
			}
		}
	}
	
	public String displayMonomial()
	{
		String str = coefficent + "x^" + degree; 
		return str;
	}
	
	public BigDecimal calculateDerivative(BigDecimal x)
	{
		BigDecimal bdcoefficent = new BigDecimal(coefficent);
		BigDecimal value = x.pow(degree);
		value = value.multiply(bdcoefficent);
		return value;
	}
	
	public int getCoefficent()
	{	return coefficent;	}
	
	public int getDegree()
	{	return degree;	}
}
