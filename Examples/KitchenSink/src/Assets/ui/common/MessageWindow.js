function MessageWindow() {
	var win = Titanium.UI.createWindow({
		height:30,
		width:250,
		bottom:70,
		borderRadius:10,
		touchEnabled:false
	});
	var messageView = Titanium.UI.createView({
		id:'messageview',
		height:30,
		width:250,
		borderRadius:10,
		backgroundColor:'#000',
		opacity:0.7,
		touchEnabled:false
	});
	var messageLabel = Titanium.UI.createLabel({
		id:'messagelabel',
		text:'',
		color:'#fff',
		width:250,
		height:'auto',
		font:{
			fontFamily:'Helvetica Neue',
			fontSize:13
		},
		textAlign:'center'
	});
		
	win.add(messageView);
	win.add(messageLabel);
	
	this.setLabel = function(_text) {
		messageLabel.text = _text;
	};
	
	this.open = function(_args) {
		win.open(_args);
	};
	
	this.close = function(_args) {
		win.close(_args);
	};
}

module.exports = MessageWindow;
