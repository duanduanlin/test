//
//  CatNode.swift
//  CatNap
//
//  Created by duan lin ding on 2024/4/6.
//

import Foundation
import SpriteKit

class CatNode: SKSpriteNode,CustomNodeEvents {
    func didMoveToScene() {
        print("cat added to scene")
        let catBodyTexture = SKTexture(imageNamed: "cat_body_outline")
        parent!.physicsBody = SKPhysicsBody(texture: catBodyTexture, size: catBodyTexture.size())
        parent!.physicsBody!.categoryBitMask = PhysicsCategory.Cat
        parent!.physicsBody!.collisionBitMask = PhysicsCategory.Block
    }
}
