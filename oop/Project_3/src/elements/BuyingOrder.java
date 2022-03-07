package elements;

/**
 * BuyingOrder is the child of the Order class.
 * Trader who gave this order will get coins and pay them with dollars.
 */
public class BuyingOrder extends Order implements Comparable<BuyingOrder> {
    /**
     * Constructor for the BuyingOrder class.
     * @param traderID id of the trader that gave the buy order.
     * @param amount amount that will be bought.
     * @param price price of the coin that will be bought.
     */
    public BuyingOrder(int traderID, double amount, double price) {
        super(traderID, amount, price);
    }

    /**
     * Implementation of the compareTo method from Comparable interface.
     * @param other the object that will be compared to.
     */
    public int compareTo(BuyingOrder other){
        if(getPrice() != other.getPrice())
            return (int)(other.getPrice() - getPrice());
        else if(getAmount() != other.getAmount())
            return (int)(other.getAmount() - getAmount());
        else
            return getTraderID() - other.getTraderID();
    }

}
