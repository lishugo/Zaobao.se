<?php
/**
 * Swedish news for Chinese audience
*/

//Call the PHP libraries we need to include
require_once('./php/includes/simplepie.inc');
require_once('./php/includes/newsblocks.inc');

header('Content-type:text/html; charset=utf-8');

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >	
<head>
	<title>早报.SE</title>
	<link rel="stylesheet" href="./css/styles.css" type="text/css" media="screen" charset="utf-8" />
	<link rel="shortcut icon" src="./icons/favicon.ico" >
	<meta http-equiv="content-type" content="text/html; charset=UTF-8" />
	<meta name="description" content="关于瑞典的中文新闻聚合, 每天十分钟了解瑞典大事小情" />
	<meta name="keywords" content="瑞典新闻, 海外新闻, 斯德哥尔摩新闻, 新闻聚合, 瑞典中文" />
	<link rel="stylesheet" href="./css/style.css" type="text/css" media="all" />
	<link rel="pingback" href="./php/xmlrpc.php" />
	<link rel="EditURI" type="application/rsd+xml" title="RSD" href="./php/xmlrpc.php?rsd" />
	<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-2796582-7']);
  _gaq.push(['_setDomainName', '.shuguo.org']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>
</head>
<body>
	<body>
	<div id="banner-nav">
		<div id="banner-nav-center">
			<ul id="banner-nav-pages">
				<div style="float:left;"><li><a title="Zaobao.se" href="http://shuguo.org/news">早报.SE</a> - 每天十分钟了解瑞典大事小情</li>
				</div>
			<div style="float:right;">
				<?php echo date("d-m-Y H:i:s"); ?>	
				<!--add weather information-->
			</div>		
			</ul>
		</div>
	</div>
	<div id="container">

		<div id="wrapper">
			<div id="content" class="narrowcolumn">
				<div id="post-1" class="post">
					<div class="news-entry">
						<!-- start 1st row -->
						<div class="clearer"></div>
						<div style="float:left;"><!-- left column -->
						<h2><a href="http://shuguo.org/news"><img width="16" height="16" border="none" src="./icons/favicon.ico"> 瑞典新闻</a></h2>
							<?php echo newsblocks::render('http://news.google.com/news?hl=en&tab=bn&ned=us&q=%E7%91%9E%E5%85%B8&ie=UTF-8&nolr=1&output=rss'); ?>
						</div>
						
						<div style="float:right;"><!-- right column -->
						<h2><a href="http://shuguo.org/news"><img width="16" height="16" border="none" src="./icons/favicon.ico"> 斯德哥尔摩新闻</a></h2>
							<?php echo newsblocks::render('http://news.google.com/news?hl=en&tab=wn&ned=us&q=%E6%96%AF%E5%BE%B7%E5%93%A5%E5%B0%94%E6%91%A9&ie=UTF-8&nolr=1&output=rss'); ?>
						</div>		
						<!-- end 1st row -->
						
						<!-- start 2nd row -->
						<div class="clearer"></div>
						<div style="float:left;"><!-- left column -->
						<h2><a href="http://shuguo.org/news"><img width="16" height="16" border="none" src="./icons/favicon.ico"> 瑞典博客</a></h2>
							<?php echo newsblocks::render('http://blogsearch.google.com/blogsearch_feeds?hl=en&client=news&q=%E7%91%9E%E5%85%B8&ie=utf-8&num=10&output=rss'); ?>
						</div>
						
						
						<div style="float:right;"><!-- right column -->
						<h2><a href="http://shuguo.org/news"><img width="16" height="16" border="none" src="./icons/favicon.ico"> 斯德哥尔摩博客</a></h2>
							<?php echo newsblocks::render('http://blogsearch.google.com/blogsearch_feeds?hl=en&client=news&q=%E6%96%AF%E5%BE%B7%E5%93%A5%E5%B0%94%E6%91%A9+-%E7%BB%BC%E5%90%88%E7%97%87&ie=utf-8&num=10&output=rss'); ?>
						</div>
						
						
											
						<!-- start flickr row -->
						<div class="clearer"></div>
						<div style="float:left;width:950px">
							<h2><a href="http://www.flickr.com/groups/photo_stockholm/"><img width="16" height="16" border="none" src="http://www.flickr.com/favicon.ico">色影斯京</a></h2>
							<?php echo newsblocks::render_flickr('http://api.flickr.com/services/feeds/groups_pool.gne?id=1029313@N23&lang=en-us&format=rss_200', array('items'=>12)); ?>
						</div>
						<!-- end flickr row -->
						
						<div class="clearer"></div>
					</div><!-- END NEWS-ENTRY -->
				</div><!-- END POST -->
				<!-- <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" 
					      xmlns:dc="http://purl.org/dc/elements/1.1/"
						  xmlns:trackback="http://madskills.com/public/xml/rss/module/trackback/">
					 <rdf:Description rdf:about="http://www.delic.com/news/?p=1"
						  dc:identifier="http://www.delic.com/news/?p=1"
						  dc:title="Hello world!"
						  trackback:ping="http://www.delic.com/news/wp-trackback.php?p=1" />
					</rdf:RDF> -->
			</div><!-- END CONTENT -->
		</div><!-- END WRAPPER -->
		<div id="footer">
			<p>&copy; <a href="http://www.shuguo.org" title="SHUGUO" rel="follow">SHUGUO</a></p>
		</div><!-- END FOOTER -->
	</div><!-- END CONTAINER -->
	<script type="text/javascript">loadMe();</script>
</body>
</html>