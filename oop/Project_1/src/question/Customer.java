
package question;

public class Customer {
	
	//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE
	final int ID;
	final String name;
	private int age;
	private Operator operator;
	private Bill bill;
	private int talkingAmount;
	private int messageCount;
	private double networkUsage;
	
	public Customer(int ID, String name, int age, Operator operator, double limitingAmount) {
		this.ID = ID;
		this.name = name;
		this.setAge(age);
		this.setOperator(operator);
		this.setBill(new Bill(limitingAmount));
		talkingAmount = 0;
		messageCount = 0;
		networkUsage = 0;
	}
	
	public void talk(int minute, Customer other) {
		if(bill.check(operator.calculateTalkingCost(minute, this)) && this != other) {
			talkingAmount += minute;
			other.talkingAmount += minute;
			operator.addTalkingAmount(minute);
			other.operator.addTalkingAmount(minute);
			bill.add(operator.calculateTalkingCost(minute, this));
		}
		
	}
	
	public void message(int quantity, Customer other) {
		if(bill.check(operator.calculateMessageCost(quantity, this, other)) && this != other) {
			messageCount += quantity;
			operator.addMessageCount(quantity);
			bill.add(operator.calculateMessageCost(quantity, this, other));
		}
		
	}
	
	public void connection(double amount) {
		if(bill.check(operator.calculateNetworkCost(amount))) {
			networkUsage += amount;
			operator.addNetworkUsage(amount);
			bill.add(operator.calculateNetworkCost(amount));
		}
		
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public Operator getOperator() {
		return operator;
	}

	public void setOperator(Operator operator) {
		this.operator = operator;
	}

	public Bill getBill() {
		return bill;
	}

	public void setBill(Bill bill) {
		this.bill = bill;
	}
	
	public int getTalkingAmount() {
		return talkingAmount;
	}
	
	public int getMessageCount() {
		return messageCount;
	}
	
	public double getNetworkUsage() {
		return (double)Math.round(networkUsage*100)/100;
	}

	//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE
}

