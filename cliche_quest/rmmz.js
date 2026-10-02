var fs   = require('fs');
var pako = require('pako');

function usage() {
	console.log("usage: [-c] file");
}

function main() {
	var compress = false;
	var args = process.argv.slice(2);
	if (args.length >= 1 && args[0] == "-c") {
		compress = true;
		args = args.slice(1);
	}
	if (args.length == 0) {
		usage();
		return;
	}

	data = fs.readFileSync(args[0]);
	if (!compress) {
		output = pako.inflate(data, { to: "string" });
	} else {
		output = pako.deflate(data, { to: "string", level: 1 });
	}
	process.stdout.write(output);
}

main();
