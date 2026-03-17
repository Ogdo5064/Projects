package classes.model.Tiles;

import java.io.Serializable;

/**
 * Represents the skeleton tile in the game
 */
public class SkeletonTile extends FindingTile implements Serializable {
    /**
     * Enum variable
     * The type of the skeleton
     * 4 types
     */
    private SkeletonType type;

    /**
     * Default constructor
     * @param type of the skeleton
     * @param points the tile points
     */
    public SkeletonTile(SkeletonType type, int points){
        super(points);
        this.type = type;
    }

    /**
     * Setter for type
     * @param type of the skeleton
     */
    public void setType(SkeletonType type){this.type = type;}

    /**
     * Getter for type
     * @return the type of the skeleton
     */
    public SkeletonType getType(){return type;}
}

