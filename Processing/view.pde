PShape body ;
PShape heart;
PShape brain ;
PShape hBrain;
PShape bBrain ;
PShape sBrain ;
PImage headShape ;

float angle = 0 ;
color[] colors = new color[2] ;
PGraphics brainTexture ;
int calcSize = 150; 
float scale = 0.1 ;
float offset = 0;
float offsetSpeed = 0.1 ; 

void setup() {
  size(1600, 900, P3D) ;
  body = loadShape("body.obj") ;
  heart = loadShape("heart.obj");
  brain = loadShape("brain.obj");
  hBrain = loadShape("half_brain.obj") ;
  bBrain = loadShape("brain_back.obj") ;
  sBrain = loadShape("brain_side.obj") ;
  headShape = loadImage("base.png") ;
  
  body.disableStyle() ;
  heart.disableStyle();
  brain.disableStyle();
  hBrain.disableStyle() ;
  bBrain.disableStyle() ;
  sBrain.disableStyle() ;
  
  brainTexture = createGraphics(calcSize, calcSize);
  brainTexture.beginDraw() ;
  brainTexture.colorMode(HSB, 360, 100, 100) ;
  brainTexture.endDraw() ;
  
  colors[0] = brainTexture.color(220, 85, 15);
  colors[1] = brainTexture.color(195, 30, 100);
  
  hBrain.setTexture(brainTexture) ;
  bBrain.setTexture(brainTexture) ;
  sBrain.setTexture(brainTexture) ;
  
  smooth(8) ;
  ortho() ;
}

void draw() {
  background(0) ;
  angle = map(mouseX, 0, width, 0, 360);
  
  
  //body
  pushMatrix();
    translate(3*width/4, height/2, 0) ;
    rotateY(radians(angle)) ;
    pushStyle() ;
      noFill() ;
      stroke(255, 10) ;
      strokeWeight(0.9);
      shape(body) ;
    popStyle() ;
  popMatrix() ;
  
  
  //heart
  pushMatrix() ;
    translate(3*width/4, (height/2)-190 , 0) ;
    rotateY(radians(angle)) ;
    pushStyle() ;
      noFill() ;
      stroke(255, 0, 0, 10) ;
      strokeWeight(0.9);
      shape(heart) ;
    popStyle() ;
  popMatrix() ;  
  
  
  //brain
  pushMatrix();
    translate(3*width/4, (height/2)-345, 0) ;
    rotateY(radians(angle)) ;
    pushStyle() ;
      noFill() ;
      stroke(255, 10) ;
      strokeWeight(0.9);
      shape(brain) ;
    popStyle() ;
  popMatrix() ;
  
  //brain animation
  brainTexture.beginDraw() ;
    brainTexture.loadPixels() ;
    for(int x=0; x<calcSize ; x++){
      for(int y=0; y<calcSize ; y++){
        float variation = noise(x * scale, y*scale, offset) ;
        color mix = brainTexture.lerpColor(colors[0], colors[1], variation) ;
        brainTexture.pixels[x + y * calcSize] = mix ;
      }
    }
    brainTexture.updatePixels() ;
  brainTexture.endDraw() ;
  
  
  pushMatrix();
    hint(DISABLE_DEPTH_TEST);
    image(headShape, 0, 0, 650, 350) ;
    hint(ENABLE_DEPTH_TEST);
    
    pushStyle() ;
      stroke(255, 20) ;
      strokeWeight(0.5) ;
      
      translate(122, 120) ;
      shape(sBrain) ;
      translate(-122, -120) ;
      
      translate(333, 160) ;
      shape(hBrain) ;
      translate(-333, -160) ;
      
      translate(538, 130) ;
      shape(bBrain) ;
      
    popStyle() ;
  popMatrix() ;
  
    pushMatrix();
    pushStyle() ;
    popStyle() ;
  popMatrix() ;
  
  offset += offsetSpeed ;
  
}
