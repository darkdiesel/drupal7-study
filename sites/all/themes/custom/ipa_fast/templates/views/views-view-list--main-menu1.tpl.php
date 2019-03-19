<?php if (!empty($title)): ?>
  <li class="menu__item">
    <?php print $title; ?>

    <ul class="menu sub-menu">
      <?php if (!empty($title)): ?>
        <li class="intro"><?php print $title; ?></li>
      <?php endif; ?>
    </ul>
  </li>
<?php endif; ?>
