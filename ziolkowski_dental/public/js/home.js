$(document).ready(function() {
  var d = new Date();
  var date = d.getDate();
  var month = d.getMonth() + 1;
  var year = d.getFullYear();
  $("#today").text("Today: " + (('' + month).length < 2 ? '0' : '') + month + "/" + (('' + date).length < 2 ? '0' : '') + date + "/" + year);
  var nextMonth;
  if (date > 15) month += 1;
  if (month == 1) nextMonth = "Febuary";
  else if (month == 2) nextMonth = "March";
  else if (month == 3) nextMonth = "April";
  else if (month == 4) nextMonth = "May";
  else if (month == 5) nextMonth = "June";
  else if (month == 6) nextMonth = "July";
  else if (month == 7) nextMonth = "August";
  else if (month == 8) nextMonth = "September";
  else if (month == 9) nextMonth = "October";
  else if (month == 10) nextMonth = "November";
  else if (month == 11) nextMonth = "December";
  else if (month == 12) nextMonth = "January";
  $("p#expiration").text("expires " + nextMonth + " 1st, " + year)
  $("form").submit(function(e) {
    e.preventDefault();
    var $this = $(this);
    $.post($this.attr("action"), $this.serialize(), function(data) {
      return data
    }, "json");
  });
});