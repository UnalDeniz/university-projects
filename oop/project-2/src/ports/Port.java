
//DO_NOT_EDIT_ANYTHING_ABOVE_THIS_LINE

package ports;

import containers.*;
import interfaces.IPort;
import ships.Ship;
import java.util.ArrayList;
import java.util.Collections;
	/**
	 * The port can contain containers and can be sailed to by ships.
	 * Each port has its own unique ID and coordinates.
	 * @author deniz ünal
	 *
	 */
public class Port implements IPort {
	/**
	 * The port ID.
	 */
	final private int ID;
	/**
	 * The X coordinate of the port.
	 */
	final private double X;
	/**
	 * The Y coordinate of the port.
	 */
	final private double Y;
	/**
	 * The containers that is currently present on the port.
	 */
	private ArrayList<Container> containers = new ArrayList<Container>();
	/**
	 * The ships that is previously docked on the port but no longer present.
	 */
	private ArrayList<Ship> history = new ArrayList<Ship>();
	/**
	 * The ships that is currently docked on the port.
	 */
	private ArrayList<Ship> current = new ArrayList<Ship>();
	/**
	 * Sets the ID, X coordinate and Y coordinate of the port.
	 * @param ID the port ID
	 * @param X the X coordinate of the port.
	 * @param Y the Y coordinate of the port.
	 */
	public Port(int ID, double X, double Y) {
		this.ID = ID;
		this.X = X;
		this.Y = Y;
	}
	/**
	 * Calculates the distance between this port and the other port in the parameter in kilometers.
	 * @param other the other port.
	 * @return the distance between the ports.
	 */
	public double getDistance(Port other) {
		double sqrX = Math.pow(this.X - other.X, 2);
		double sqrY = Math.pow(this.Y - other.Y, 2);
		return Math.sqrt(sqrY + sqrX);
	}
	/**
	 * Adds the incoming ship to docked ships.
	 * @param the ship that will be docked to this port.
	 */
	public void incomingShip(Ship s) {
		current.add(s);
	}
	/**
	 * Removes the outgoing ship from docked ships and adds it to history of ships.
	 * @param the ship that will depart from the port.
	 */
	public void outgoingShip(Ship s) {
		current.remove(s);
		if(!history.contains(s)) {
			history.add(s);
		}
	}
	/**
	 * Getter method for the containers ArrayList.
	 * @return the containers ArrayList
	 */
	public ArrayList<Container> getContainers() {
		Collections.sort(containers);
		return containers;
	}
	/**
	 * Returns X and Y coordinates of the port within parantheses.
	 * @return X and Y coordinates of the port.
	 */
	public String getCoordinates() {
		return "(" + String.format("%.2f", X) + ", " + String.format("%.2f", Y) + ")";
	}
	/**
	 * Returns the basic containers on the port.
	 * @return basic containers on the port.
	 */
	public ArrayList<Container> getBasicContainers(){
		ArrayList<Container> basicContainers = new ArrayList<Container>();
		for(Container c:getContainers()) {
			if(c instanceof BasicContainer)
				basicContainers.add(c);
		}
		return basicContainers;
	}
	/**
	 * Returns the heavy containers on the port that is not liquid or refrigerated.
	 * @return heavy containers on the port that is not liquid or refrigerated.
	 */
	public ArrayList<Container> getOnlyHeavyContainers(){
		ArrayList<Container> onlyHeavyContainers = new ArrayList<Container>();
		for(Container c:getContainers()) {
			if(c instanceof HeavyContainer&&!(c instanceof LiquidContainer)&&!(c instanceof RefrigeratedContainer)) {
				onlyHeavyContainers.add(c);
			}
		}
		return onlyHeavyContainers;
	}
	/**
	 * Returns the liquid containers on the port.
	 * @return liquid containers on the port.
	 */
	public ArrayList<Container> getLiquidContainers(){
		ArrayList<Container> liquidContainers = new ArrayList<Container>();
		for(Container c:getContainers()) {
			if(c instanceof LiquidContainer)
				liquidContainers.add(c);
		}
		return liquidContainers;
	}
	/**
	 * Returns the refrigerated containers on the port.
	 * @return refrigerated containers on the port.
	 */
	public ArrayList<Container> getRefrigeratedContainers(){
		ArrayList<Container> refrigeratedContainers = new ArrayList<Container>();
		for(Container c:getContainers()) {
			if(c instanceof RefrigeratedContainer)
				refrigeratedContainers.add(c);
		}
		return refrigeratedContainers;
	}
	/**
	 * Getter method for the current ArrayList.
	 * @return the current ArrayList.
	 */
	public ArrayList<Ship> getCurrent(){
		Collections.sort(current);
		return current;
	}
}



//DO_NOT_EDIT_ANYTHING_BELOW_THIS_LINE

