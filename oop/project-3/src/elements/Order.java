package elements;

/**
 * Order is the parent of the SellingOrder and BuyingOrder classes.
 */
public abstract class Order {

    private final double amount;
    private final double price;
    private final int traderID;

    /**
     * Constructor class for the Order class.
     * @param traderID id of the trader that gave the order.
     * @param amount amount of the coins that will be used in transaction.
     * @param price price of coin in the order.
     */
    public Order(int traderID, double amount, double price){
        this.traderID = traderID;
        this.amount = amount;
        this.price = price;
    }

    /**
     * Getter method for the amount.
     * @return returns the amount of coins in the order.
     */
    public double getAmount(){
        return amount;
    }

    /**
     * Getter method for the price.
     * @return price of coin in the order.
     */
    public double getPrice(){
        return price;
    }

    /**
     * Getter method for the traderID.
     * @return id of the trader that gave the order.
     */
    public int getTraderID(){
        return traderID;
    }
}

