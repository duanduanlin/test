import SpriteKit

class GameScene:SKScene{
    //添加背景1作为精灵
    let background = SKSpriteNode(imageNamed: "background1")
    //添加一个僵尸
    let zombie = SKSpriteNode(imageNamed: "zombie1")
    //添加时间统计变量
    var lastUpdateTime: TimeInterval = 0
    var dt: TimeInterval = 0
    //移动速度
    let zombieMovePointPerSec: CGFloat = 480.0
    //速度向量
    var velocity = CGPoint.zero
    
    func moveSprite(sprite: SKSpriteNode, velocity: CGPoint){
        let amountToMove = CGPoint(x: velocity.x*CGFloat(dt), y: velocity.y*CGFloat(dt))
        
        print("Amount to move: \(amountToMove)")
        
        sprite.position = CGPoint(x: sprite.position.x + amountToMove.x, y: sprite.position.y + amountToMove.y)
    }
    
    func moveZombieToward(location: CGPoint){
        let offset = CGPoint(x: location.x - zombie.position.x, y: location.y - zombie.position.y)
        let length = sqrt(Double(offset.x * offset.x + offset.y * offset.y))
        let direction = CGPoint(x: offset.x / CGFloat(length), y: offset.y / CGFloat(length))
        velocity = CGPoint(x: direction.x * zombieMovePointPerSec, y: direction.y * zombieMovePointPerSec)
    }
    
    func sceneTouched(touchLocation: CGPoint){
        moveZombieToward(location: touchLocation)
    }
    
    func boundsCheckZombie(){
        let bounds:CGRect = view?.bounds ?? CGRect(x: 0, y: 0, width: size.width, height: size.height)
//        print("bounds: \(bounds)")
        let bottmLeft = CGPoint.zero
        let topRight = CGPoint(x: bounds.width, y: bounds.height)
        
        if zombie.position.x <= bottmLeft.x{
            zombie.position.x = bottmLeft.x
            velocity.x = -velocity.x
        }
        
        if zombie.position.x >= topRight.x{
            zombie.position.x = topRight.x
            velocity.x = -velocity.x
        }
        
        if zombie.position.y <= bottmLeft.y{
            zombie.position.y = bottmLeft.y
            velocity.y = -velocity.y
        }
        
        if zombie.position.y >= topRight.y {
            zombie.position.y = topRight.y
            velocity.y = -velocity.y
        }
    }
    
    override func didMove(to view: SKView) {
        //设置背景颜色
        backgroundColor = SKColor.black
        
        //设置图片位置为居中显示
        background.position = CGPoint(x: size.width/2, y: size.height/2)
        //将背景图片置于最后
        background.zPosition = -1
        
        //放置僵尸
        zombie.position = CGPoint(x: 400, y: 400)
        //放大两倍
        //        zombie.setScale(2)
        //或者设置精灵的锚点
        //        background.anchorPoint = CGPoint.zero
        //        background.position = CGPoint.zero
        //尝试旋转精灵
        //        background.zRotation = CGFloat(Double.pi) / 8
        //添加精灵
        addChild(background)
        addChild(zombie)
        //        let mysize = background.size
        //        print("size:\(mysize)")
    }
    
    override func update(_ currentTime: TimeInterval) {
        moveSprite(sprite: zombie, velocity: velocity)
        //        zombie.position = CGPoint(x: zombie.position.x + 8, y: zombie.position.y + 8)
        if lastUpdateTime > 0{
            dt = currentTime - lastUpdateTime
        }else{
            dt = 0
        }
        lastUpdateTime = currentTime
        print("\(dt*1000) ms since last update")
        boundsCheckZombie()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return
        }
        let touchLocation = touch.location(in: self)
        sceneTouched(touchLocation: touchLocation)
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return
        }
        let touchLocation = touch.location(in: self)
        sceneTouched(touchLocation: touchLocation)
    }
}
