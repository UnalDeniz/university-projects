package elements;

/**
 * SellingOrder is the child of the Order class.
 * Trader who gave this order will sell coins and get dollars in exchange.
 */
public class SellingOrder extends Order implements Comparable<SellingOrder> {
    /**
     * Constructor for the SellingOrder class.
     * @param traderID id of the trader that gave the sell order.
     * @param amount amount that will be sold.
     * @param price price of the coin that will be sold.
     */
    public SellingOrder(int traderID, double amount, double price) {
        super(traderID, amount, price);
    }

    /**
     * Implementation of the compareTo method from Comparable interface.
     * @param other the object that will be compared to.
     */
    public int compareTo(SellingOrder other){
        if(getPrice() != other.getPrice())
            return (int)(getPrice() - other.getPrice());
        else if(getAmount() != other.getAmount())
            return (int)(other.getAmount() - getAmount());
        else
            return getTraderID() - other.getTraderID();
    }

}
