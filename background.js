var embed = document.createElement('embed');
embed.setAttribute("src", "out/main.nmf");
embed.setAttribute("width", "1");
embed.setAttribute("height", "1");
embed.setAttribute("type", "application/x-pnacl");
var div = document.createElement("div");
document.body.appendChild(div);

div.addEventListener("load", function () {
	console.log("LODED");
}, true);

div.addEventListener("message", function (evt) {
	console.log(evt.data);
}, true);

div.appendChild(embed);
