package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the finding tile of the game
 * Every tile except LandSlides is a FindingTile
 */
public class FindingTile extends Tile implements Serializable {

    /**
     * Default constructor
     * @param points of the tile
     */
    public FindingTile(int points){
        super(points);
    }

}
