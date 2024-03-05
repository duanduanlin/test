//
//  MainMenuScene.swift
//  ZombieConga
//
//  Created by duan lin ding on 2024/3/5.
//

import Foundation
import SpriteKit

class MainMenuScene: SKScene {
    
    /// 处理触摸
    func sceneTapped(){
        let actionBlock = SKAction.run{
            let myScene = GameScene(size: self.size)
            myScene.scaleMode = self.scaleMode
            let reveal = SKTransition.doorsOpenHorizontal(withDuration: 1.5)
            self.view?.presentScene(myScene, transition: reveal)
        }
        
        self.run(actionBlock)
    }
    
    override func didMove(to view: SKView) {
        let background: SKSpriteNode = SKSpriteNode(imageNamed: "MainMenu")
        
        background.position = CGPoint(x: self.size.width / 2, y: self.size.height / 2)
        self.addChild(background)
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return
        }
        sceneTapped()
    }
}
