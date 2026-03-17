package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the vase tile in the game
 */
public class VaseTile extends FindingTile implements Serializable {

    /**
     * Default constructor
     * @param points the tile points
     */
    public VaseTile(int points){
        super(points);
    }
}
