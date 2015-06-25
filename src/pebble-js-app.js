Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received message: ' + JSON.stringify(e));
  }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    var dict = {
      'COMMAND_KEY' : 'GET_SETTINGS'
    };
    Pebble.sendAppMessage(dict,
        function(ee) {
          Pebble.openURL("https://rawgit.com/pekha/pebble-plockTwo-face/nico/configurable.html");
        },
        function(ee) {
          Pebble.openURL("https://rawgit.com/pekha/pebble-plockTwo-face/nico/configurable.html");
        }
      );      
    
  }
);
Pebble.addEventListener("webviewclosed",
  function(e) {
    if (e.data != "CANCELLED"){
      console.log('webviewclosed: ' + JSON.stringify(e));
      var configuration = JSON.parse(decodeURIComponent(e.data));
      var dict = {
        'BACKGROUND_KEY' : parseInt(configuration.background, 16),
        'LETTER_ON_KEY' : parseInt(configuration.letter_on, 16),
        'LETTER_OFF_KEY' : parseInt(configuration.letter_off, 16),
        'THINER_OFF_FONT_KEY' : configuration.thiner_off_font,
        'COMMAND_KEY' : 'SET_SETTINGS'
      };
      
      console.log('Dict: ' + JSON.stringify(dict));
      
      // Send a string to Pebble
      Pebble.sendAppMessage(dict,
        function(ee) {
          console.log('Send successful.' + ee);
        },
        function(ee) {
          console.log('Unable to deliver message with transactionId='+JSON.stringify(ee));
        }
      );      
    }
  }
);