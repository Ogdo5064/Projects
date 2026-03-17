package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the statue tile in the game
 */
public class StatueTile extends FindingTile implements Serializable {

    /**
     * Default constructor
     * @param points the tile points
     */
    public StatueTile(int points){
        super(points);
    }
}
