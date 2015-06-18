Pebble.addEventListener("showConfiguration",
  function(e) {
    Pebble.openURL("data:/config.html");
  }
);
Pebble.addEventListener("webviewclosed",
  function(e) {
    var configuration = e.response.split(";");
    var dict = {
      'BACKGROUND_KEY' : parseInt(configuration[0], 16),
      'LETTER_ON_KEY' : parseInt(configuration[2], 16),
      'LETTER_OFF_KEY' : parseInt(configuration[1], 16)
    //  'THINER_OFF_FONT_KEY'
    };

    // Send a string to Pebble
    Pebble.sendAppMessage(dict,
      function(e) {
        console.log('Send successful.');
      },
      function(e) {
        console.log('Send failed!');
      }
    );
  }
);