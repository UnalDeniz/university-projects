package executable;

import elements.Market;
import elements.Trader;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

/**
 * Main class is the executable class. Reads input, and print outputs into file.
 */
public class Main {

    public static Random myRandom;

    /**
     * Main method reads queries from input and calls necessary methods from other classes.
     * @param args input file, output file.
     */
    public static void main(String[] args) throws FileNotFoundException {

        Scanner in = new Scanner(new File(args[0]));
        PrintStream out = new PrintStream(new File(args[1]));

        int seed = in.nextInt();
        myRandom = new Random(seed);
        Market market = new Market(in.nextInt());
        ArrayList<Trader> traders = new ArrayList<>();

        int traderCount = in.nextInt();
        int queryCount = in.nextInt();
        int invalidCount = 0;

        for(int i=0; i<traderCount; i++){
            double dollarAmount = in.nextDouble();
            double pqoinAmount = in.nextDouble();
            traders.add(new Trader(dollarAmount, pqoinAmount));
        }

        for(int j=0; j<queryCount; j++){
            int queryType = in.nextInt();
            if(queryType == 10){
                //give buying order for specific price
                int traderID = in.nextInt();
                double price = in.nextDouble();
                double amount = in.nextDouble();
                invalidCount += traders.get(traderID).buy(amount, price, market);
                market.checkTransactions(traders);
            } else if(queryType == 11){
                //give buying order for market price
                int traderID = in.nextInt();
                double amount = in.nextDouble();
                if(market.emptyBuyOrders())
                    invalidCount++;
                else
                    invalidCount += traders.get(traderID).buy(amount, market.getBuyingPrice(), market);
                market.checkTransactions(traders);
            } else if(queryType == 20){
                //give selling order for specific price
                int traderID = in.nextInt();
                double price = in.nextDouble();
                double amount = in.nextDouble();
                invalidCount += traders.get(traderID).sell(amount, price, market);
                market.checkTransactions(traders);
            } else if(queryType == 21){
                //give selling order for market price
                int traderID = in.nextInt();
                double amount = in.nextDouble();
                if(market.emptySellOrders())
                    invalidCount++;
                else
                    invalidCount += traders.get(traderID).sell(amount, market.getSellingPrice(), market);
                market.checkTransactions(traders);
            } else if(queryType == 3){
                //deposit dollars to wallet
                int traderID = in.nextInt();
                double amount = in.nextDouble();
                traders.get(traderID).getWallet().depositDollars(amount);
            } else if(queryType == 4){
                //withdraw dollars from wallet
                int traderID = in.nextInt();
                double amount = in.nextDouble();
                invalidCount += traders.get(traderID).getWallet().withdrawDollars(amount);
            } else if(queryType == 5){
                //print wallet status
                int traderID = in.nextInt();
                out.println(traders.get(traderID).printWalletStatus());
            } else if(queryType == 777){
                //give rewards to all traders
                for(Trader t:traders){
                    double reward = myRandom.nextDouble()*10;
                    t.getWallet().addCoins(reward);
                }
            } else if(queryType == 666){
                //make open market operation
                double price = in.nextDouble();
                market.makeOpenMarketOperation(price, traders);
            } else if(queryType == 500){
                // print the current market size
                out.println(market.printMarketSize());
            } else if(queryType == 501){
                //print number of successful transactions
                out.println(market.transactionCount());
            } else if(queryType == 502){
                //print the number of invalid queries
                out.println("Number of invalid queries: " +invalidCount);
            } else if(queryType == 505){
                // print the current prices
                out.println(market.printCurrentPrices());
            } else if(queryType == 555){
                //print all traders’ wallet status
                for(Trader t:traders){
                    out.println(t.printWalletStatus());
                }
            }
        }
        
        in.close();
        out.close();
    }
}

