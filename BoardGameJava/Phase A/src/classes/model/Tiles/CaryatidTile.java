package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the caryatid tile in the game
 */
public class CaryatidTile extends StatueTile implements Serializable {

    /**
     * Default constructor
     * @param points of the tile
     */
    public CaryatidTile(int points){
        super(points);
    }
}
