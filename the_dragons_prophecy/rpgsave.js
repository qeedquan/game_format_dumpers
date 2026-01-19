var fs       = require('fs');
var LZString = require('./lz-string.js');

function usage() {
	console.log("usage: [-c] file");
}

function main() {
	var compress = false;
	var args = process.argv.slice(2);
	if (args.length >= 1 && args[0] == "-e") {
		compress = true;
		args = args.slice(1);
	}
	if (args.length == 0) {
		usage();
		return;
	}

	data = fs.readFileSync(args[0], { encoding: 'utf8' });
	if (compress) {
		output = LZString.compressToBase64(data);
	} else {
		output = LZString.decompressFromBase64(data);
	}
	process.stdout.write(output);
}

main();
