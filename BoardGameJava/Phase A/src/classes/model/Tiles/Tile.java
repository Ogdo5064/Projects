package classes.model.Tiles;

import java.io.Serializable;

/**
 * Parent class of all tiles
 * Represents a tile in the game
 *
 * @author Dimokritos Bompos
 * @version 1.0
 */
public abstract class Tile implements Serializable {

    /**
     * Represents the tile's points
     */
    private int points;

    /**
     *
     * @param points of the tile
     * Default constructor every tile uses
     */
    public Tile(int points){
        this.points = points;
    }

    /**
     * Getter
     * @return the points of the tile
     */
    public int getPoints(){return points;}

    /**
     * Setter
     * @param points of the tile
     */
    public void setPoints(int points){this.points = points;}

}
