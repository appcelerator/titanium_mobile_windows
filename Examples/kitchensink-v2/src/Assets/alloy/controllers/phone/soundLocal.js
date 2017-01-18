function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function startPlayback() {
        soundPlayer.play();
        $.playbackProgress.setMax(1e3 * soundPlayer.getDuration());
    }
    function pausePlayback() {
        soundPlayer.pause();
    }
    function resetPlayback() {
        soundPlayer.reset();
        $.playbackProgress.setValue(0);
    }
    function setVolumeUp() {
        if (soundPlayer.getVolume() < 1) {
            soundPlayer.setVolume(soundPlayer.volume += .1);
            $.buttonVolumeUp.setTitle("Volume++ (" + Math.round(1e3 * soundPlayer.getVolume()) / 1e3 + ")");
            $.buttonVolumeDown.setTitle("Volume--");
        }
    }
    function setVolumeDown() {
        if (soundPlayer.getVolume() > 0) {
            soundPlayer.setVolume(soundPlayer.getVolume() < .1 ? 0 : soundPlayer.volume -= .1);
            $.buttonVolumeDown.setTitle("Volume-- (" + Math.round(1e3 * soundPlayer.getVolume()) / 1e3 + ")");
            $.buttonVolumeUp.setTitle("Volume++");
        }
    }
    function toggleLooping() {
        soundPlayer.setLooping(!soundPlayer.getLooping());
        $.buttonLooping.setTitle("Looping (" + soundPlayer.isLooping() + ")");
    }
    function onPlaybackComplete() {
        $.playbackProgress.setValue(0);
    }
    function onPlaybackResume() {
        log.args("Ti.Media.Sound", "The sound player was resumed!");
    }
    function startInterval() {
        playbackInterval = setInterval(function() {
            if (soundPlayer.isPlaying()) {
                $.playbackProgress.setValue(soundPlayer.getTime());
                log.args("Ti.Media.Sound", "Time: " + soundPlayer.getTime());
            }
        }, 500);
    }
    function stopInterval() {
        clearInterval(playbackInterval);
        soundPlayer.release();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "phone/soundLocal";
    this.args = arguments[0] || {};
    if (arguments[0]) {
        {
            __processArg(arguments[0], "__parentSymbol");
        }
        {
            __processArg(arguments[0], "$model");
        }
        {
            __processArg(arguments[0], "__itemTemplate");
        }
    }
    var $ = this;
    var exports = {};
    var __defers = {};
    $.__views.soundLocal = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Local Sound",
        id: "soundLocal"
    });
    $.__views.soundLocal && $.addTopLevelView($.__views.soundLocal);
    startInterval ? $.addListener($.__views.soundLocal, "open", startInterval) : __defers["$.__views.soundLocal!open!startInterval"] = true;
    stopInterval ? $.addListener($.__views.soundLocal, "close", stopInterval) : __defers["$.__views.soundLocal!close!stopInterval"] = true;
    $.__views.__alloyId148 = Ti.UI.createView({
        layout: "vertical",
        width: 300,
        id: "__alloyId148"
    });
    $.__views.soundLocal.add($.__views.__alloyId148);
    $.__views.__alloyId149 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "Start",
        id: "__alloyId149"
    });
    $.__views.__alloyId148.add($.__views.__alloyId149);
    startPlayback ? $.addListener($.__views.__alloyId149, "click", startPlayback) : __defers["$.__views.__alloyId149!click!startPlayback"] = true;
    $.__views.__alloyId150 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "Stop",
        id: "__alloyId150"
    });
    $.__views.__alloyId148.add($.__views.__alloyId150);
    pausePlayback ? $.addListener($.__views.__alloyId150, "click", pausePlayback) : __defers["$.__views.__alloyId150!click!pausePlayback"] = true;
    $.__views.__alloyId151 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "Reset",
        id: "__alloyId151"
    });
    $.__views.__alloyId148.add($.__views.__alloyId151);
    resetPlayback ? $.addListener($.__views.__alloyId151, "click", resetPlayback) : __defers["$.__views.__alloyId151!click!resetPlayback"] = true;
    $.__views.__alloyId152 = Ti.UI.createView({
        height: Ti.UI.SIZE,
        id: "__alloyId152"
    });
    $.__views.__alloyId148.add($.__views.__alloyId152);
    $.__views.buttonVolumeUp = Ti.UI.createButton({
        width: 140,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        left: 0,
        id: "buttonVolumeUp",
        title: "Volume++"
    });
    $.__views.__alloyId152.add($.__views.buttonVolumeUp);
    setVolumeUp ? $.addListener($.__views.buttonVolumeUp, "click", setVolumeUp) : __defers["$.__views.buttonVolumeUp!click!setVolumeUp"] = true;
    $.__views.buttonVolumeDown = Ti.UI.createButton({
        width: 140,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        right: 0,
        id: "buttonVolumeDown",
        title: "Volume--"
    });
    $.__views.__alloyId152.add($.__views.buttonVolumeDown);
    setVolumeDown ? $.addListener($.__views.buttonVolumeDown, "click", setVolumeDown) : __defers["$.__views.buttonVolumeDown!click!setVolumeDown"] = true;
    $.__views.buttonLooping = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        id: "buttonLooping",
        title: "Looping (false)"
    });
    $.__views.__alloyId148.add($.__views.buttonLooping);
    toggleLooping ? $.addListener($.__views.buttonLooping, "click", toggleLooping) : __defers["$.__views.buttonLooping!click!toggleLooping"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var soundPlayer, playbackInterval, log = require("log");
    !function() {
        Ti.Media.setAudioSessionCategory(Ti.Media.AUDIO_SESSION_CATEGORY_AMBIENT);
        soundPlayer = Titanium.Media.createSound({
            url: "sounds/cricket.wav"
        });
        soundPlayer.addEventListener("complete", onPlaybackComplete);
        soundPlayer.addEventListener("resume", onPlaybackResume);
    }();
    __defers["$.__views.soundLocal!open!startInterval"] && $.addListener($.__views.soundLocal, "open", startInterval);
    __defers["$.__views.soundLocal!close!stopInterval"] && $.addListener($.__views.soundLocal, "close", stopInterval);
    __defers["$.__views.__alloyId149!click!startPlayback"] && $.addListener($.__views.__alloyId149, "click", startPlayback);
    __defers["$.__views.__alloyId150!click!pausePlayback"] && $.addListener($.__views.__alloyId150, "click", pausePlayback);
    __defers["$.__views.__alloyId151!click!resetPlayback"] && $.addListener($.__views.__alloyId151, "click", resetPlayback);
    __defers["$.__views.buttonVolumeUp!click!setVolumeUp"] && $.addListener($.__views.buttonVolumeUp, "click", setVolumeUp);
    __defers["$.__views.buttonVolumeDown!click!setVolumeDown"] && $.addListener($.__views.buttonVolumeDown, "click", setVolumeDown);
    __defers["$.__views.buttonLooping!click!toggleLooping"] && $.addListener($.__views.buttonLooping, "click", toggleLooping);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;