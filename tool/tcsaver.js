//Testcase Auto Downloader
//Requirements: node(v14), competitive companion(web browser extension)
//How to use
//1. install [competitive companion] on web browser
//2. run this server ([Allow Automatic Tasks] of VSCode might be convenient)
//3. click green (+) button on browser in problem page
//4. build your code and run testtc.sh
const app = require('express')();
const bodyParser = require('body-parser');
const port = 10043;
app.use(bodyParser.json());
app.post('/', (req, res) => {
  const data = req.body;
  console.log('['+data.name+'] parsed.');
	fs = require('fs');
	if(fs.existsSync('test'))
		fs.rmdirSync('test',{recursive:true});
	fs.mkdirSync('test');
	for(let i=0;i<data.tests.length;i++){
		if(!i){
			fs.writeFileSync('test/in', data.tests[i].input);
			fs.writeFileSync('test/ans', data.tests[i].output);
		}
		fs.writeFileSync('test/'+i+'.in', data.tests[i].input);
		fs.writeFileSync('test/'+i+'.ans', data.tests[i].output);
	}
  res.sendStatus(200);
});
app.listen(port, "localhost", err => {console.log('Server started.');});
