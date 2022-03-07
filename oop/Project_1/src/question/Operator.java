
package question;

public class Operator {
	//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE
	final int ID;
	private double talkingCharge;
	private double messageCost;
	private double networkCharge;
	private int discountRate;
	private int talkingAmount;
	private int messageCount;
	private double networkUsage;
	
	public Operator(int ID, double talkingCharge, double messageCost, double networkCharge, int discountRate) {
		this.ID = ID;
		this.setTalkingCharge(talkingCharge);
		this.setMessageCost(messageCost);
		this.setNetworkCharge(networkCharge);
		this.setDiscountRate(discountRate);
		talkingAmount = 0;
		messageCount = 0;
		networkUsage = 0;
	}
	
	public double calculateTalkingCost(int minute, Customer customer) {
		double cost;
		if(customer.getAge() < 18 || customer.getAge() > 65) {
			cost = talkingCharge * minute * (1 - (double)discountRate/100);
		} else {
			cost = talkingCharge * minute;
		}
		return cost;
	}
	
	public double calculateMessageCost(int quantity, Customer customer, Customer other) {
		double cost;
		if(customer.getOperator() == other.getOperator()) {
			cost = messageCost * quantity * (1 - (double)discountRate/100);
		} else {
			cost = messageCost * quantity;
		}
		return cost;
	}
	
	public double calculateNetworkCost(double amount) {
		double cost;
		cost = amount * networkCharge;
		return cost;
	}

	public double getTalkingCharge() {
		return talkingCharge;
	}

	public void setTalkingCharge(double talkingCharge) {
		this.talkingCharge = talkingCharge;
	}

	public double getMessageCost() {
		return messageCost;
	}

	public void setMessageCost(double messageCost) {
		this.messageCost = messageCost;
	}

	public double getNetworkCharge() {
		return networkCharge;
	}

	public void setNetworkCharge(double networkCharge) {
		this.networkCharge = networkCharge;
	}

	public int getDiscountRate() {
		return discountRate;
	}

	public void setDiscountRate(int discountRate) {
		this.discountRate = discountRate;
	}
	
	public int getTalkingAmount() {
		return talkingAmount;
	}
	
	public void addTalkingAmount(int amount) {
		talkingAmount += amount;
	}
	
	public int getMessageCount() {
		return messageCount;
	}
	
	public void addMessageCount(int amount) {
		messageCount += amount;
	}
	
	public double getNetworkUsage() {
		return (double)Math.round(networkUsage*100)/100;
	}
	
	public void addNetworkUsage(double amount) {
		networkUsage += amount;
	}

	//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE
}

