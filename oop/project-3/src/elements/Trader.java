package elements;

/**
 * Traders are the individuals that carries out the transactions in the market.
 * Each trader has a unique id and wallet and can put a buy/sell order in the market.
 */
public class Trader {

    public static int numberOfUsers = 0;

    private final int id;
    private final Wallet wallet;

    /**
     * Constructor for the Trader class.
     * @param dollars amount of dollars the trader has at the beginning.
     * @param coins amount of coins the trader has at the beginning.
     */
    public Trader(double dollars, double coins){
        id = numberOfUsers;
        numberOfUsers++;
        wallet = new Wallet(dollars, coins);
    }

    /**
     * Creates a selling order and calls the giveSellOrder method from the market.
     * @param amount the amount which will be sold.
     * @param price the price that is going to sold from.
     * @param market the market which the coins will be sold in.
     * @return 0 if trader has enough coins to sell, 1 otherwise.
     */
    public int sell(double amount, double price, Market market){
        if(wallet.getCoins() >= amount){
            SellingOrder sellOrder = new SellingOrder(id, amount, price);
            market.giveSellOrder(sellOrder);
            wallet.blockCoins(amount);
            return 0;
        } else
            return 1;
    }

    /**
     *Creates a buying order and calls the giveBuyOrder method from the market.
     * @param amount the amount which will be bought.
     * @param price the price that is going to bought from.
     * @param market the market which the coins will be bought in.
     * @return 0 if trader has enough dollar to buy, 1 otherwise.
     */
    public int buy(double amount, double price, Market market){
        if(wallet.getDollars() >= (amount * price)){
            BuyingOrder buyOrder = new BuyingOrder(id, amount, price);
            market.giveBuyOrder(buyOrder);
            wallet.blockDollars(amount * price);
            return 0;
        } else
            return 1;
    }

    /**
     * Getter method for the wallet.
     * @return wallet of the trader.
     */
    public Wallet getWallet(){
        return wallet;
    }

    /**
     * Getter method for the id.
     * @return id of the trader.
     */
    public int getId(){
        return id;
    }

    /**
     * Returns the wallet status as a string.
     * @return the wallet status.
     */
    public String printWalletStatus(){
        return "Trader "+id+": "+wallet.getTotalDollars()+"$ "+wallet.getTotalCoins()+"PQ";
    }
}
