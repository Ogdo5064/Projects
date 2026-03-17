package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the sphinx tile in the game
 */
public class SphinxTile extends StatueTile implements Serializable {
    /**
     * Default constructor
     * @param points the tile points
     */
    public SphinxTile(int points){
        super(points);
    }
}
