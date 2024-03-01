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
    //游戏区域
    let playableRect: CGRect
    //上次触摸位置
    var lastTouchLocation: CGPoint?
    //旋转速度
    let zombieRotateRadiansPerSec:CGFloat = 4.0 * π
    
    func moveSprite(sprite: SKSpriteNode, velocity: CGPoint){
        let amountToMove = velocity * CGFloat(dt)
        print("Amount to move: \(amountToMove)")
        sprite.position += amountToMove
    }
    
    func moveZombieToward(location: CGPoint){
        let offset = location - zombie.position
        let direction = offset.normalized()
        velocity = direction * zombieMovePointPerSec
    }
    
    func sceneTouched(touchLocation: CGPoint){
        lastTouchLocation = touchLocation
        moveZombieToward(location: touchLocation)
    }
    
    func boundsCheckZombie(){
//        let viewSize = viewSizeInLocalCoordinates()
        let bottmLeft = CGPoint(x: 0, y: CGRectGetMinY(playableRect))
        let topRight = CGPoint(x: size.width, y: CGRectGetMaxY(playableRect))
        
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
    
    func debugDrawPlayableArea(){
        let shape = SKShapeNode()
        let path = CGMutablePath()
        path.addRect(playableRect)
      
        shape.path = path
        shape.strokeColor = SKColor.red
        shape.lineWidth = 4.0
        addChild(shape)
    }
    
    func rotateSprite(sprite: SKSpriteNode, direction: CGPoint, rotateRadiansPerSec: CGFloat){
        let shortest:CGFloat = shortestAngleBetween(angle1: direction.angle, angle2: sprite.zRotation)
        var amtToRotate:CGFloat = rotateRadiansPerSec * dt
        if abs(shortest) < amtToRotate{
            amtToRotate = shortest
        }
        sprite.zRotation += amtToRotate*amtToRotate.sign()
    }
    
    override init(size: CGSize){
        let maxAspectRatio:CGFloat = 16.0/9.0
        let playableHeight = size.width / maxAspectRatio
        let playableMargin = (size.height - playableHeight) / 2.0
        playableRect = CGRect(x: 0, y: playableMargin, width: size.width, height: playableHeight)
        super.init(size: size)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
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
        debugDrawPlayableArea()
    }
    
    override func update(_ currentTime: TimeInterval) {
        
        //        zombie.position = CGPoint(x: zombie.position.x + 8, y: zombie.position.y + 8)
        if lastUpdateTime > 0{
            dt = currentTime - lastUpdateTime
        }else{
            dt = 0
        }
        lastUpdateTime = currentTime
        print("\(dt*1000) ms since last update")
        boundsCheckZombie()
        
        if let stopPoint = lastTouchLocation{
            if (stopPoint - zombie.position).length() < zombieMovePointPerSec * dt{
                zombie.position = stopPoint
                velocity = CGPoint.zero
            }else{
                moveSprite(sprite: zombie, velocity: velocity)
                rotateSprite(sprite: zombie, direction: velocity, rotateRadiansPerSec: zombieRotateRadiansPerSec)
            }
        }
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
//extension CGPoint {
//    static func +(lhs: CGPoint, rhs: CGPoint) -> CGPoint {
//        return CGPoint(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
//    }
//    static func -(lhs: CGPoint, rhs: CGPoint) -> CGPoint {
//        return CGPoint(x: lhs.x - rhs.x, y: lhs.y - rhs.y)
//    }
//}
//
//extension SKScene {
//    func viewSizeInLocalCoordinates() -> CGSize {
//        let reference = CGPoint(x: view!.bounds.maxX, y: view!.bounds.maxY)
//        let bottomLeft = convertPoint(fromView: .zero)
//        let topRight = convertPoint(fromView: reference)
//        let d = topRight - bottomLeft
//        return CGSize(width: abs(d.x), height: abs(d.y))
//    }
//}
