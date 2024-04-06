import SpriteKit
import PlaygroundSupport

let sceneView = SKView(frame: CGRect(x: 0, y: 0, width: 480, height: 320))

let scene = SKScene(size: CGSize(width: 480, height: 320))
scene.physicsWorld.gravity = CGVector(dx: 0, dy: 0)
scene.physicsBody = SKPhysicsBody(edgeLoopFrom: scene.frame)
sceneView.showsFPS = true
sceneView.showsPhysics = true
sceneView.presentScene(scene)

PlaygroundPage.current.needsIndefiniteExecution = true
PlaygroundPage.current.liveView = sceneView

let square = SKSpriteNode(imageNamed: "square")
square.name = "shape"
square.position = CGPoint(x: scene.size.width*0.25, y: scene.size.height*0.5)

let circle = SKSpriteNode(imageNamed: "circle")
circle.name = "shape"
circle.position = CGPoint(x: scene.size.width*0.5, y: scene.size.height*0.5)
circle.physicsBody?.isDynamic = false

let triangle = SKSpriteNode(imageNamed: "triangle")
triangle.name = "shape"
triangle.position = CGPoint(x: scene.size.width*0.75, y: scene.size.height*0.5)

let l = SKSpriteNode(imageNamed: "L")
l.name = "shape"
l.position = CGPoint(x: scene.size.width*0.5, y: scene.size.height*0.75)

circle.physicsBody = SKPhysicsBody(circleOfRadius: circle.size.width / 2)
square.physicsBody = SKPhysicsBody(rectangleOf: square.frame.size)
l.physicsBody = SKPhysicsBody(texture: l.texture!, size: l.size)

var trianglePath = CGMutablePath()
trianglePath.move(to: CGPoint(x: -triangle.size.width / 2, y: -triangle.size.height / 2))
trianglePath.addLine(to: CGPoint(x: triangle.size.width / 2, y: -triangle.size.height / 2))
trianglePath.addLine(to: CGPoint(x: 0, y: triangle.size.height / 2))
trianglePath.addLine(to: CGPoint(x: -triangle.size.width / 2, y: -triangle.size.height / 2))
triangle.physicsBody = SKPhysicsBody(polygonFrom: trianglePath)

scene.addChild(square)
scene.addChild(triangle)
scene.addChild(circle)
scene.addChild(l)

func spawnSand(){
    let sand = SKSpriteNode(imageNamed: "sand")
    sand.position = CGPoint(x: random(min: 0, max: scene.size.width), y:scene.size.height - sand.size.height )
    
    sand.physicsBody = SKPhysicsBody(circleOfRadius: sand.size.width / 2)
    sand.physicsBody!.restitution = 1.0
    sand.physicsBody!.density=20.0
    sand.name = "sand"
    scene.addChild(sand)
}

func shake(){
    scene.enumerateChildNodes(withName: "sand"){node,_ in
        node.physicsBody!.applyImpulse(CGVector(dx: 0, dy: random(min: 20, max: 40)))
    }
    scene.enumerateChildNodes(withName: "shape"){node,_ in
        node.physicsBody!.applyImpulse(CGVector(dx: 0, dy: random(min: 20, max: 40)))
    }
}
delay(second: 2.0, complete: {
    scene.physicsWorld.gravity = CGVector(dx: 0, dy: -9.8)
    scene.run(SKAction.repeat(SKAction.sequence([SKAction.run(spawnSand),SKAction.wait(forDuration: 0.1)]), count: 100))
    
    delay(second: 12, complete: shake)
})

var blowwingRight = true
var windForce = CGVector(dx: 50, dy: 0)

extension SKScene{
    @objc func windWithTimer(timer:Timer){
        scene?.enumerateChildNodes(withName: "sand"){node,_ in
            node.physicsBody!.applyForce(windForce, at: node.frame.origin)
        }
        scene?.enumerateChildNodes(withName: "shape"){node,_ in
            node.physicsBody!.applyForce(windForce, at: node.frame.origin)
        }
    }
    
    @objc func switchWindDirection(timer:Timer){
        blowwingRight = !blowwingRight
        windForce = CGVector(dx: blowwingRight ? 50 : -50, dy: 0)
    }
}

Timer.scheduledTimer(timeInterval: 0.05, target: scene, selector: #selector(SKScene.windWithTimer), userInfo: nil, repeats: true)

Timer.scheduledTimer(timeInterval: 3, target: scene, selector: #selector(SKScene.switchWindDirection), userInfo: nil, repeats: true)
