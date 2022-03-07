package elements;

/**
 * Transaction  holds the selling and buying orders that was used in successful transactions.
 */
public class Transaction {

    private final SellingOrder sellingOrder;
    private final BuyingOrder buyingOrder;

    /**
     * Constructor for the Transaction class.
     * @param sellingOrder selling order that will be used in transaction.
     * @param buyingOrder buying order that will be used in transaction.
     */
    public Transaction(SellingOrder sellingOrder, BuyingOrder buyingOrder){
        this.sellingOrder = sellingOrder;
        this.buyingOrder = buyingOrder;
    }

}
