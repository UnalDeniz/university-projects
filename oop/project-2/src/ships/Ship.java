
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package ships;

import interfaces.IShip;
import ports.Port;
import containers.BasicContainer;
import containers.Container;
import containers.HeavyContainer;
import containers.LiquidContainer;
import containers.RefrigeratedContainer;

import java.util.ArrayList;
import java.util.Collections;
	/**
	 * The ship can sail to ports and can carry containers.
	 * Each ship has its own unique ID, fuel consumption, weight limitations 
	 * and container number limitations.
	 * @author deniz ünal
	 *
	 */
public class Ship implements IShip, Comparable<Ship> {
	/**
	 * The ship ID.
	 */
	final private int ID;
	/**
	 * The amount of fuel the ship currently has.
	 */
	private double fuel;
	/**
	 * The port that the ship is docked to.
	 */
	private Port currentPort;
	/**
	 * The maximum amount of weight the ship can carry.
	 */
	final private int totalWeightCapacity;
	/**
	 * The maximum number of containers the ship can carry.
	 */
	final private int maxNumberOfAllContainers;
	/**
	 * The maximum number of heavy containers the ship can carry.
	 */
	final private int maxNumberOfHeavyContainers;
	/**
	 * The maximum number of refrigerated containers the ship can carry.
	 */
	final private int maxNumberOfRefrigeratedContainers;
	/**
	 * The maximum number of liquid containers the ship can carry.
	 */
	final private int maxNumberOfLiquidContainers;
	/**
	 * The amount of consumption of the ship per kilometers.
	 */
	final private double fuelConsumptionPerKM;
	/**
	 * The containers that is currently loaded on the ship.
	 */
	private ArrayList<Container> currentContainers = new ArrayList<Container>();
	/**
	 * Sets the container limitations, fuel consumption, starting port and ID of the ship.
	 * @param ID the ship ID.
	 * @param p the starting port.
	 * @param totalWeightCapacity the maximum amount of weight the ship can carry.
	 * @param maxNumberOfAllContainers the maximum number of containers the ship can carry.
	 * @param maxNumberOfHeavyContainers the maximum number of heavy containers the ship can carry.
	 * @param maxNumberOfRefrigeratedContainers the maximum number of refrigerated containers the ship can carry.
	 * @param maxNumberOfLiquidContainers the maximum number of liquid containers the ship can carry.
	 * @param fuelConsumptionPerKM the amount of consumption of the ship per kilometers.
	 */
	public Ship(int ID, Port p, int totalWeightCapacity, int maxNumberOfAllContainers, int maxNumberOfHeavyContainers, 
			int maxNumberOfRefrigeratedContainers, int maxNumberOfLiquidContainers, double fuelConsumptionPerKM) {
		this.ID = ID;
		this.currentPort = p;
		p.getCurrent().add(this);
		this.totalWeightCapacity = totalWeightCapacity;
		this.maxNumberOfAllContainers = maxNumberOfAllContainers;
		this.maxNumberOfHeavyContainers = maxNumberOfHeavyContainers;
		this.maxNumberOfRefrigeratedContainers = maxNumberOfRefrigeratedContainers;
		this.maxNumberOfLiquidContainers = maxNumberOfLiquidContainers;
		this.fuelConsumptionPerKM = fuelConsumptionPerKM;
	}
	/**
	 * Getter method for the currentContainers ArrayList.
	 * @return the currentContainers ArrayList.
	 */
	public ArrayList<Container> getCurrentContainers(){
		Collections.sort(currentContainers);
		return currentContainers;
	}
	/**
	 * Checks if it is possible to sail to port in the parameters.
	 * Compares the total consumption required to sail with the fuel
	 * the ship has, if the ship has enough fuel returns true and sail to that port.
	 * @param p the port that is planned to sail.
	 */
	public boolean sailTo(Port p) {
		if(fuel >= travelConsumption(p)) {
			fuel -= travelConsumption(p);
			currentPort.outgoingShip(this);
			p.incomingShip(this);
			currentPort = p;
			return true;
		} else {
			return false;
		}
	}
	/**
	 * Calculates the required fuel amount to sail to the port on the parameters.
	 * @param p the destination.
	 * @return the required amount of fuel.
	 */
	private double travelConsumption(Port p) {
		double containerConsumption = 0;
		for(Container c:currentContainers) {
			containerConsumption += c.consumption();
		}
		return (containerConsumption + fuelConsumptionPerKM) * currentPort.getDistance(p);
	}
	/**
	 * Adds fuel to the ship.
	 * @param newFuel the amount of fuel that will be added to the ship.
	 */
	public void reFuel(double newFuel) {
		fuel += newFuel;
	}
	/**
	 * Checks if it is possible to load the container in the parameters to ship.
	 * Calculates the number of containers and total weight after loading,
	 * if it exceeds the ship limitations or the container does not exist 
	 * in the port, returns false otherwise, returns true and loads the container.
	 * @param cont the container that is planned to load into the ship.
	 */
	public boolean load(Container cont) {
		if(!currentPort.getContainers().contains(cont))
			return false;
		if(currentContainers.size() + 1 > maxNumberOfAllContainers)
			return false;
		if(cont.getWeight() + getCurrentContainerWeight() > totalWeightCapacity)
			return false;
		if(cont instanceof HeavyContainer) {
			if(getHeavyContainers().size() + 1 > maxNumberOfHeavyContainers)
				return false;
			if(cont instanceof LiquidContainer) {
				if(getLiquidContainers().size()+ 1 > maxNumberOfLiquidContainers)
					return false;
			}
			if(cont instanceof RefrigeratedContainer) {
				if(getRefrigeratedContainers().size() + 1 > maxNumberOfRefrigeratedContainers)
					return false;
			}
		}
		currentContainers.add(cont);
		currentPort.getContainers().remove(cont);
		return true;
	}
	/**
	 * Checks if it is possible to unload the container in the parameters from ship.
	 * Checks if the container is present on the ship, if it is returns true and 
	 * unloads the container.
	 * @param cont the container that is planned to unload from the ship.
	 */
	public boolean unLoad(Container cont) {
		if(currentContainers.contains(cont)) {
			currentPort.getContainers().add(cont);
			currentContainers.remove(cont);
			return true;
		} else {
			return false;
		}
	}
	/**
	 * compareTo method for the ship class.
	 * Compares the ship IDs.
	 */
	public int compareTo(Ship other) {
		return this.ID - other.ID;
	}
	/**
	 * Calculates the total weight of the containers that is loaded on the ship.
	 * @return the total weight of the containers.
	 */
	private int getCurrentContainerWeight() {
		int currentContainerWeight = 0;
		for(Container c:currentContainers) {
			currentContainerWeight += c.getWeight();
		}
		return currentContainerWeight;
	}
	/**
	 * Getter method for the ship ID.
	 * @return the ship ID.
	 */
	public int getID() {
		return ID;
	}
	/**
	 * Returns the amount of fuel the ship has with 2 digits after the fraction point.
	 * @return the amount of fuel.
	 */
	public String getFuel() {
		return String.format("%.2f", fuel);
	}
	/**
	 * Returns the basic containers that is loaded on the ship.
	 * @return the basic containers on the ship.
	 */
	public ArrayList<Container> getBasicContainers(){
		ArrayList<Container> basicContainers = new ArrayList<Container>();
		for(Container c:currentContainers) {
			if(c instanceof BasicContainer)
				basicContainers.add(c);
		}
		Collections.sort(basicContainers);
		return basicContainers;
	}
	/**
	 * Returns the heavy containers on the ship including liquid and refrigerated containers.
	 * @return the heavy containers on the ship including liquid and refrigerated containers.
	 */
	public ArrayList<Container> getHeavyContainers(){
		ArrayList<Container> heavyContainers = new ArrayList<Container>();
		for(Container c:currentContainers) {
			if(c instanceof HeavyContainer)
				heavyContainers.add(c);
		}
		Collections.sort(heavyContainers);
		return heavyContainers;
	}
	/**
	 * Returns the heavy containers on the ship excluding liquid and refrigerated containers.
	 * @return the heavy containers on the ship excluding liquid and refrigerated containers.
	 */
	public ArrayList<Container> getOnlyHeavyContainers(){
		ArrayList<Container> onlyHeavyContainers = new ArrayList<Container>();
		for(Container c:currentContainers) {
			if(c instanceof HeavyContainer&&!(c instanceof LiquidContainer)&&!(c instanceof RefrigeratedContainer))
				onlyHeavyContainers.add(c);
		}
		Collections.sort(onlyHeavyContainers);
		return onlyHeavyContainers;
	}
	/**
	 * Returns the liquid containers that is loaded on the ship.
	 * @return the liquid containers on the ship.
	 */
	public ArrayList<Container> getLiquidContainers(){
		ArrayList<Container> liquidContainers = new ArrayList<Container>();
		for(Container c:currentContainers) {
			if(c instanceof LiquidContainer)
				liquidContainers.add(c);
		}
		Collections.sort(liquidContainers);
		return liquidContainers;
	}
	/**
	 * Returns the refrigerated containers that is loaded on the ship.
	 * @return the refrigerated containers on the ship.
	 */
	public ArrayList<Container> getRefrigeratedContainers(){
		ArrayList<Container> refrigeratedContainers = new ArrayList<Container>();
		for(Container c:currentContainers) {
			if(c instanceof RefrigeratedContainer)
				refrigeratedContainers.add(c);
		}
		Collections.sort(refrigeratedContainers);
		return refrigeratedContainers;
	}
	
}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

