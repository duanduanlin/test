import Foundation

public func delay(second:Double, complete:@escaping ()->()){
    let popTime = DispatchTime.now
    
    DispatchQueue.main.asyncAfter(deadline: popTime()+second,execute:complete)
}

public func random(min: CGFloat,max:CGFloat) -> CGFloat{
    return CGFloat(Float(arc4random()) / Float(0xFFFFFFFF)) * (max - min) + min
}
