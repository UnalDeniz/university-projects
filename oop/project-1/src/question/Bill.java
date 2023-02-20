
package question;

public class Bill {

	//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE
	private double limitingAmount;
	private double currentDebt;
	private double moneySpent;
	
	public Bill(double limitingAmount) {
		this.limitingAmount = limitingAmount;
		currentDebt = 0;
		moneySpent = 0;
	}
	
	public boolean check(double amount) {
		return amount + currentDebt <= limitingAmount;
	}
	
	public void add(double amount) {
		currentDebt += amount;
	}
	
	public void pay(double amount) {
		if(amount < currentDebt) {
			currentDebt -= amount;
			moneySpent += amount;
		} else {
			moneySpent += currentDebt;
			currentDebt = 0;
		}
	}
	
	public void changeTheLimit(double amount) {
		if(amount >= currentDebt) {
			limitingAmount = amount;
		}
	}

	public double getLimitingAmount() {
		return limitingAmount;
	}
	
	public double getCurrentDebt() {
		return (double)Math.round(currentDebt*100)/100;
	}

	public double getMoneySpent() {
		return (double)Math.round(moneySpent*100)/100;
	}
	

	//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE
}

