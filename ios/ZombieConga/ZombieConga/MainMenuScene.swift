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
        let myScene = GameScene(size:self.size)
        myScene.scaleMode = scaleMode
        let reveal = SKTransition.doorway(withDuration: 1.5)
        self.view?.presentScene(myScene, transition: reveal)
    }
    
    override func didMove(to view: SKView) {
        let background: SKSpriteNode = SKSpriteNode(imageNamed: "MainMenu")
        
        background.position = CGPoint(x: self.size.width / 2, y: self.size.height / 2)
        self.addChild(background)
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        sceneTapped()
    }
}
