package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the landslide tile
 */
public class LandslideTile extends Tile implements Serializable {

    /**
     * Default constructor
     * @param points of the tile
     */
    public LandslideTile(int points){
        super(points);
    }
}
