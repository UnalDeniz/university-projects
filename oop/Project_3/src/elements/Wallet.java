package elements;

/**
 * Wallet holds the amount of coins and dollars each trader have and performs the individual actions.
 */
public class Wallet {

    private double dollars;
    private double coins;
    private double blockedDollars;
    private double blockedCoins;

    /**
     * Constructor for the Wallet class.
     * @param dollars the dollar amount at the beginning.
     * @param coins the PQoin amount at the beginning.
     */
    public Wallet(double dollars, double coins){
        this.dollars = dollars;
        this.coins = coins;
    }

    /**
     * Getter method for the dollars.
     * @return the unblocked dollar amount.
     */
    public double getDollars(){
        return dollars;
    }

    /**
     * Returns both the unblocked and blocked dollars with 5 decimals after the point.
     * @return total dollar amount.
     */
    public String getTotalDollars(){
        return String.format("%.5f", dollars + blockedDollars);
    }

    /**
     * Getter method for the coins.
     * @return the unblocked coin amount.
     */
    public double getCoins(){
        return coins;
    }

    /**
     * Returns both the unblocked and blocked coins with 5 decimals after the point.
      * @return total coin amount.
     */
    public String getTotalCoins(){
        return String.format("%.5f", coins + blockedCoins);
    }

    /**
     * Withdraws dollar if there is enough dollar in the wallet.
     * @param amount the amount which will be withdrawn.
     * @return 0 if there are enough dollars, 1 otherwise.
     */
    public int withdrawDollars(double amount){
        if(dollars >= amount){
            dollars -= amount;
            return 0;
        } else
            return 1;
    }

    /**
     * Deposits dollar to the wallet.
     * @param amount the amount which will be deposited.
     */
    public void depositDollars(double amount){
        dollars += amount;
    }

    /**
     * Adds coins to the wallet.
     * @param amount the amount which will be added.
     */
    public void addCoins(double amount){
        coins += amount;
    }

    /**
     * Blocks a certain amount of dollars.
     * @param amount the amount which will be blocked.
     */
    public void blockDollars(double amount){
        dollars -= amount;
        blockedDollars += amount;
    }

    /**
     * Spends the blocked dollars in order to make a transaction.
     * @param amount the amount which will be spent.
     */
    public void spendDollars(double amount){
        blockedDollars -= amount;
    }

    /**
     * Blocks a certain amount of coins.
     * @param amount the amount which will be blocked.
     */
    public void blockCoins(double amount){
        coins -= amount;
        blockedCoins += amount;
    }

    /**
     * Spends the blocked coins in order to make a transaction.
     * @param amount the amount which will be spent.
     */
    public void spendCoins(double amount){
        blockedCoins -= amount;
    }

}
