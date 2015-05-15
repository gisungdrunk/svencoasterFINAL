#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    //load type
    ofTrueTypeFont::setGlobalDpi(72);
    
    verdana14.loadFont("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    
    verdana14A.loadFont("verdana.ttf", 14, false);
    verdana14A.setLineHeight(18.0f);
    verdana14A.setLetterSpacing(1.037);
    
    
    
    
    
    ofSetVerticalSync(true);
    
    // load an image from disk
    img.loadImage("sven.png");
    
    
    //    img.loadImage("sven2.png");
    //linzer.png
    
    // we're going to load a ton of points into an ofMesh
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    
    
    // loop through the image in the x and y axes
    int skip = 4; // load a subset of the points
    for(int y = 0; y < img.getHeight(); y += skip) {
        for(int x = 0; x < img.getWidth(); x += skip) {
            ofColor cur = img.getColor(x, y);
            if(cur.a > 0) {
                // the alpha value encodes depth, let's remap it to a good depth range
                float z = ofMap(cur.a, 0, 255, -500, 300);
                cur.a = 255;
                mesh.addColor(cur);
                ofVec3f pos(x, y, z);
                mesh.addVertex(pos);
            }
        }
    }
    
    
    ofEnableDepthTest();
    //glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(4); // make the points bigger
    
    
    
    // added another one
    
    
    
    
    ofSetVerticalSync(true);
    
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();
    
    // ofBox uses texture coordinates from 0-1, so you can load whatever
    // sized images you want and still use them to texture your box
    // but we have to explicitly normalize our tex coords here
    ofEnableNormalizedTexCoords();
    
    // loads the OF logo from disk
    ofLogo.loadImage("sven.png");
    
    //    sven.loadImage("sven.png");
    
    // draw the ofBox outlines with some weight
    //	ofSetLineWidth(10);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetColor(20, 20, 20);
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // all the strings!
    ofSetColor(255);
    string fullscreen = "push F to allow full screen";
    ofDrawBitmapString(fullscreen, 20, 20);
    string title = "welcome to sventure!(Sven version of adventure)";
    ofDrawBitmapString(title, 20, 30);
    
    string msg = "it's a svencoaster/svenpillar!!";
    ofDrawBitmapString(msg, 20, 700);
    string msg2 = "drag mouse to see the 3d of svencoaster!!!";
    ofDrawBitmapString(msg2, 20, 750);
    
    
    //verdana14.drawString("this is verdana", 50, 50);
    verdana14.drawString("Font Example - use keyboard to type", 30, 35);
    
    
    
    
    float movementSpeed = .1;
    float cloudSize = ofGetWidth() / 2;
    float maxBoxSize = 150;
    float spacing = 1;
    int boxCount = 80;
    
    //------------ added
    ofBackgroundGradient(0, ofColor::white, OF_GRADIENT_CIRCULAR);
    
    //original
    cam.begin();
    
    
    //------------ added
    ofScale(2, -2, 2); // flip the y axis and zoom in a bit
    ofRotateY(90);
    ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
    mesh.draw();
    //------------ added
    
    
    //original
    for(int i = 0; i < boxCount; i++) {
        
        ofPushMatrix();
        
        //original
        //		float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
        float t = (ofGetElapsedTimef() + i * 0.1) * 0.2;
        
        // ofVec3f pos(x, y, z)
        ofVec3f pos(
                    ofSignedNoise(t, 0, 30),
                    ofSignedNoise(10, t, 40),
                    ofSignedNoise(20, 40, t));
        
        float boxSize = maxBoxSize * ofNoise(pos.x, pos.y, pos.z);
        // boxsize = 150 * ofNoise()
        
        pos *= cloudSize;
        //cloudsize = 200;
        
        ofTranslate(pos);
        ofRotateX(pos.x);
        ofRotateY(pos.y);
        ofRotateZ(pos.z);
        
        ofLogo.bind();
        ofFill();
        ofSetColor(255);
        ofDrawBox(boxSize);
        ofLogo.unbind();
        
        ofNoFill();
        ofDrawBox(boxSize * 1.1f);
        ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
        ofPopMatrix();
    }
    
    cam.end();
    
    
    
//    ofPushMatrix();
//    string rotZ = "Rotate Z";
//    ofRectangle bounds = verdana14.getStringBoundingBox(rotZ, 0, 0);
//    
//    ofTranslate(110 + bounds.width/2, 500 + bounds.height / 2, 0);
//    ofRotateZ(ofGetElapsedTimef() * -60.0);
//				
//    verdana14.drawString(rotZ, -bounds.width/2, bounds.height/2 );
//    ofPopMatrix();
//    ofPushMatrix();
//    
//    string scaleAA = "SCALE AA";
//    bounds = verdana14.getStringBoundingBox(scaleAA, 0, 0);
//    
//    ofTranslate(500 + bounds.width/2, 480 + bounds.height / 2, 0);
//    ofScale(2.0 + sin(ofGetElapsedTimef()), 2.0 + sin(ofGetElapsedTimef()), 1.0);
//				
//    verdana14.drawString(scaleAA, -bounds.width/2, bounds.height/2 );
//    ofPopMatrix();
    
//    ofPushMatrix();
//    string scaleA = "SCALE ALIASED";
//    ofRectangle bounds = verdana14.getStringBoundingBox("", 0, 0);
//    bounds = verdana14A.getStringBoundingBox(scaleA, 0, 0);
//    
//    ofTranslate(500 + bounds.width/2, 530 + bounds.height / 2, 0);
//    ofScale(2.0 + cos(ofGetElapsedTimef()), 2.0 + cos(ofGetElapsedTimef()), 1.0);
//				
//    verdana14A.drawString(scaleA, -bounds.width/2, bounds.height/2 );
//    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
