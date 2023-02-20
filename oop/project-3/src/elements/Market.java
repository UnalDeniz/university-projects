package elements;

import java.util.ArrayList;
import java.util.PriorityQueue;

/**
 * Market is the place which all transactions take place.
 * Holds the information about current orders and past transactions.
 */
public class Market {

    private final PriorityQueue<SellingOrder> sellingOrders = new PriorityQueue<>();
    private final PriorityQueue<BuyingOrder> buyingOrders = new PriorityQueue<>();
    private final ArrayList<Transaction> transactions = new ArrayList<>();
    private final int fee;

    /**
     * Constructor  method for the Market class.
     * @param fee the amount which market will get from transactions per thousand dollars.
     */
    public Market(int fee){
        this.fee = fee;
    }

    /**
     * Adds a new selling order to the market.
     * @param order the order that will be added.
     */
    public void giveSellOrder(SellingOrder order){
        sellingOrders.add(order);
    }

    /**
     * Checks if the sellingOrders is empty or not.
     * @return true if empty, false otherwise.
     */
    public boolean emptySellOrders(){
        return sellingOrders.isEmpty();
    }

    /**
     * Adds a new buying order to the market.
     * @param order the order that will be added.
     */
    public void giveBuyOrder(BuyingOrder order){
        buyingOrders.add(order);
    }

    /**
     * Checks if the buyingOrders is empty or not.
     * @return true if empty, false otherwise.
     */
    public boolean emptyBuyOrders(){
        return buyingOrders.isEmpty();
    }

    /**
     * Makes open market operations to bring price to a desired level.
     * @param price the desired price level.
     */
    public void makeOpenMarketOperation(double price, ArrayList<Trader> traders){
        while(getBuyingPrice() <= price && !emptySellOrders()){
            SellingOrder nextSellingOrder = sellingOrders.peek();
            buyingOrders.add(new BuyingOrder(0, nextSellingOrder.getAmount(), nextSellingOrder.getPrice()));
            checkTransactions(traders);
        }
        while(getSellingPrice() >= price && !emptyBuyOrders()){
            BuyingOrder nextBuyingOrder = buyingOrders.peek();
            sellingOrders.add(new SellingOrder(0, nextBuyingOrder.getAmount(), nextBuyingOrder.getPrice()));
            checkTransactions(traders);
        }
    }

    /**
     * Checks if there is overlapping buying and selling orders. If there is, makes transactions.
     * @param traders list of traders in the market.
     */
    public void checkTransactions(ArrayList<Trader> traders){
        while(getSellingPrice() >= getBuyingPrice() && !emptySellOrders()){
            BuyingOrder firstBuyOrder = buyingOrders.poll();
            SellingOrder firstSellOrder = sellingOrders.poll();
            double sellPrice = firstBuyOrder.getPrice();
            double buyPrice = firstSellOrder.getPrice();
            double buyAmount = firstBuyOrder.getAmount();
            double sellAmount = firstSellOrder.getAmount();
            Trader buyer = traders.get(firstBuyOrder.getTraderID());
            Trader seller = traders.get(firstSellOrder.getTraderID());
            BuyingOrder transactionBuyOrder;
            SellingOrder transactionSellOrder;
            if(buyAmount > sellAmount){
                BuyingOrder remainingBuyOrder = new BuyingOrder(buyer.getId(),buyAmount-sellAmount,sellPrice);
                transactionBuyOrder = new BuyingOrder(buyer.getId(),sellAmount,sellPrice);
                buyingOrders.add(remainingBuyOrder);
                transactionSellOrder = firstSellOrder;
            } else if(sellAmount > buyAmount){
                SellingOrder remainingSellOrder = new SellingOrder(seller.getId(),sellAmount-buyAmount,buyPrice);
                transactionSellOrder = new SellingOrder(seller.getId(),buyAmount,buyPrice);
                sellingOrders.add(remainingSellOrder);
                transactionBuyOrder = firstBuyOrder;
            } else {
                transactionBuyOrder = firstBuyOrder;
                transactionSellOrder = firstSellOrder;
            }
            transactions.add(new Transaction(transactionSellOrder,transactionBuyOrder));
            buyer.getWallet().addCoins(transactionBuyOrder.getAmount());
            buyer.getWallet().spendDollars(transactionBuyOrder.getAmount() * sellPrice);
            buyer.getWallet().depositDollars(transactionBuyOrder.getAmount() * (sellPrice - buyPrice));
            seller.getWallet().depositDollars(transactionSellOrder.getAmount() * buyPrice * (1-(double)fee/1000));
            seller.getWallet().spendCoins(transactionSellOrder.getAmount());
        }
    }

    /**
     * Returns the amount of dollars and coins in the market with 5 decimals after the point.
     * @return amount of dollars and coins in the market.
     */
    public String printMarketSize(){
        double pqoinAmount = 0;
        double dollarAmount = 0;
        for(BuyingOrder b:buyingOrders){
            dollarAmount += b.getAmount() * b.getPrice();
        }
        for(SellingOrder s:sellingOrders){
            pqoinAmount += s.getAmount();
        }
        return "Current market size: " + String.format("%.5f", dollarAmount) + " " + String.format("%.5f", pqoinAmount);
    }

    /**
     * Returns the average of the buying price and selling price.
     * If one of them is missing returns the other, and if both of them is missing returns 0.
     * @return average of buying and selling price.
     */
    public double getCurrentPrice(){
        if(buyingOrders.isEmpty() && sellingOrders.isEmpty())
            return 0;
        else if(buyingOrders.isEmpty())
            return sellingOrders.peek().getPrice();
        else if(sellingOrders.isEmpty())
            return buyingOrders.peek().getPrice();
        else
            return (buyingOrders.peek().getPrice() + sellingOrders.peek().getPrice()) / 2;
    }

    /**
     * Returns the price of cheapest selling order.
     * If there is no order returns 0.
     * @return price of cheapest selling order.
     */
    public double getBuyingPrice(){
        if(!sellingOrders.isEmpty())
            return sellingOrders.peek().getPrice();
        else
            return 0;
    }

    /**
     * Returns the price of the most expensive buying order.
     * If there is no order returns 0.
     * @return price of the most expensive buying order
     */
    public double getSellingPrice(){
        if(!buyingOrders.isEmpty())
            return buyingOrders.peek().getPrice();
        else
            return 0;
    }

    /**
     * Returns the selling price, buying price and average price with 5 decimals after the point.
     * @return selling, buying and average price.
     */
    public String printCurrentPrices(){
        return "Current prices: "+String.format("%.5f",getSellingPrice())+" "+String.format("%.5f",getBuyingPrice())+" "+String.format("%.5f",getCurrentPrice());
    }

    /**
     * Returns the amount of successful transactions.
     * @return the amount of successful transactions.
     */
    public String transactionCount(){
        return "Number of successful transactions: " + transactions.size();
    }
}
