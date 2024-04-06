//
//  BedNode.swift
//  CatNap
//
//  Created by duan lin ding on 2024/4/6.
//

import Foundation
import SpriteKit

class BedNode: SKSpriteNode, CustomNodeEvents {
    func didMoveToScene() {
        print("bed added to scene")
        let bedBodySize = CGSize(width: 40, height: 30)
        physicsBody = SKPhysicsBody(rectangleOf: bedBodySize)
        physicsBody!.isDynamic = false
        
        physicsBody!.categoryBitMask = PhysicsCategory.Bed
        physicsBody!.collisionBitMask = PhysicsCategory.None
    }
}
